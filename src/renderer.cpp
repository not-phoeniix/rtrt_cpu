#include "renderer.h"

#include "math_utils.h"
#include "interval.h"
#include "vec2.h"
#include <cstring>

constexpr uint32_t SAMPLES_PER_PIXEL = 30;
constexpr uint32_t SCANLINES_PER_FRAME = 4;
constexpr uint32_t RAY_MAX_DEPTH = 50;
constexpr float RAY_SURFACE_OFFSET = 0.001f;

Renderer::Renderer(uint32_t width, uint32_t height, float low_res_scale)
  : full_width(width),
    full_height(height),
    low_res_width((uint32_t)(width * low_res_scale)),
    low_res_height((uint32_t)(height * low_res_scale)),
    low_res_scale(low_res_scale),
    low_res(false),
    thread_pool() {
    low_res_pixels = new uint8_t[low_res_width * low_res_height * 4];
}

Renderer::~Renderer() {
    delete[] low_res_pixels;
}

void Renderer::UpdateVectors(const Camera& camera, uint32_t width, uint32_t height) {
    viewport_right = camera.get_right() * camera.get_viewport_width();
    viewport_down = -camera.get_up() * camera.get_viewport_height();
    pixel_right = viewport_right / (float)width;
    pixel_down = viewport_down / (float)height;
    viewport_top_left = camera.get_position() +
                        camera.get_forward() * camera.get_focal_length() -
                        (viewport_right / 2.0f) -
                        (viewport_down / 2.0f);
    viewport_top_left += (pixel_right * 0.5f);
    viewport_top_left += (pixel_down * 0.5f);
}

Vec3f Renderer::ShadePixel(const Ray& ray, const HittableList& objects, uint32_t max_rays) {
    if (max_rays == 0) {
        return {0, 0, 0};
    }

    HitData hit_data;
    if (objects.Hit(ray, Interval(RAY_SURFACE_OFFSET, INFINITY_F), &hit_data)) {
        Ray scattered({0, 0, 0}, {0, 0, 0});
        Vec3f attenuation;
        if (hit_data.material->Scatter(ray, hit_data, &attenuation, &scattered)) {
            return attenuation * ShadePixel(scattered, objects, max_rays - 1);
        }

        return {0, 0, 0};
    }

    Vec3f dir_norm = Vec3f::normalize(ray.get_direction());
    float a = 0.5f * (dir_norm.y + 1.0f);
    return Utils::lerp({1.0f, 1.0f, 1.0f}, {0.5f, 0.7f, 1.0f}, a);
}

void Renderer::RenderBatch(uint32_t i_start, uint32_t count, const Vec3f& cam_pos, uint8_t* pixels, uint32_t width, const HittableList& objects) {
    for (uint32_t i = i_start; i < i_start + count; i++) {
        uint32_t y = i / width;
        uint32_t x = i - (y * width);

        Vec3f color = {0.0f, 0.0f, 0.0f};
        for (uint32_t i = 0; i < SAMPLES_PER_PIXEL; i++) {
            Ray r = get_ray(x, y, cam_pos);
            color += ShadePixel(r, objects, RAY_MAX_DEPTH);
        }
        color /= (float)SAMPLES_PER_PIXEL;

        color.x = Utils::correct_gamma(color.x);
        color.y = Utils::correct_gamma(color.y);
        color.z = Utils::correct_gamma(color.z);

        static const Interval intensity(0.0f, 1.0f);
        pixels[i * 4 + 0] = (uint8_t)(intensity.Clamp(color.x) * 255.0f);
        pixels[i * 4 + 1] = (uint8_t)(intensity.Clamp(color.y) * 255.0f);
        pixels[i * 4 + 2] = (uint8_t)(intensity.Clamp(color.z) * 255.0f);
        pixels[i * 4 + 3] = 255;
    }
}

void Renderer::CopyPixelsBatch(uint32_t i_start, uint32_t count, uint8_t* out_pixels) {
    for (uint32_t i = i_start; i < i_start + count; i++) {
        uint32_t y = i / full_width;
        uint32_t x = i - (y * full_width);

        uint32_t low_res_x = (uint32_t)(x * low_res_scale);
        uint32_t low_res_y = (uint32_t)(y * low_res_scale);
        uint32_t sample_index = low_res_y * low_res_width + low_res_x;

        memcpy(
            &out_pixels[i * 4],
            &low_res_pixels[sample_index * 4],
            4
        );
    }
}

Ray Renderer::get_ray(uint32_t x, uint32_t y, const Vec3f& cam_pos) const {
    Vec2f rand_offset = {
        Utils::randf_range(-0.5f, 0.5f),
        Utils::randf_range(-0.5f, 0.5f)
    };

    Vec3f frag_screen_pos = viewport_top_left +
                            (pixel_right * (x + rand_offset.x)) +
                            (pixel_down * (y + rand_offset.y));
    Vec3f ray_dir = frag_screen_pos - cam_pos;

    return Ray(cam_pos, ray_dir);
}

void Renderer::RenderLowRes(uint8_t* pixels, const Camera& camera, const HittableList& objects) {
    Vec3f cam_pos = camera.get_position();

    UpdateVectors(camera, low_res_width, low_res_height);

    // send shading in grouped-together batches
    //   if we send them off all scattered then cache misses
    //   will cause serious performance hits

    uint32_t pixel_index_start = 0;
    uint32_t pixels_remaining = low_res_width * low_res_height;

    for (uint32_t i = 0; i < thread_pool.get_thread_count(); i++) {
        uint32_t count = low_res_width * low_res_height / thread_pool.get_thread_count();
        if (count > pixels_remaining) count = pixels_remaining;

        thread_pool.QueueJob(
            [this, pixel_index_start, count, &cam_pos, &objects](uint32_t thread_index) {
                RenderBatch(pixel_index_start, count, cam_pos, low_res_pixels, low_res_width, objects);
            }
        );

        pixel_index_start += count;
        pixels_remaining -= count;
    }

    thread_pool.Wait();

    // if we're in low res mode we render to the lower
    //   res array and copy over to the output using
    //   the thread pool when we're done

    pixel_index_start = 0;
    pixels_remaining = full_width * full_height;

    for (uint32_t i = 0; i < thread_pool.get_thread_count(); i++) {
        uint32_t count = full_width * full_height / thread_pool.get_thread_count();
        if (count > pixels_remaining) count = pixels_remaining;

        thread_pool.QueueJob(
            [this, pixel_index_start, count, pixels](uint32_t thread_index) {
                CopyPixelsBatch(pixel_index_start, count, pixels);
            }
        );

        pixel_index_start += count;
        pixels_remaining -= count;
    }

    thread_pool.Wait();
}

void Renderer::RenderFullRes(uint8_t* pixels, const Camera& camera, const HittableList& objects) {
    Vec3f cam_pos = camera.get_position();

    UpdateVectors(camera, full_width, full_height);

    // send shading in grouped-together batches
    //   if we send them off all scattered then cache misses
    //   will cause serious performance hits

    static uint32_t scanline = 0;

    uint32_t pixel_index_start = scanline * full_width;
    uint32_t pixels_remaining = full_width * SCANLINES_PER_FRAME;

    for (uint32_t i = 0; i < thread_pool.get_thread_count(); i++) {
        uint32_t count = full_width * full_height / thread_pool.get_thread_count();
        if (count > pixels_remaining) count = pixels_remaining;

        thread_pool.QueueJob(
            [this, pixel_index_start, count, &cam_pos, pixels, &objects](uint32_t thread_index) {
                RenderBatch(pixel_index_start, count, cam_pos, pixels, full_width, objects);
            }
        );

        pixel_index_start += count;
        pixels_remaining -= count;
    }

    thread_pool.Wait();
    scanline += SCANLINES_PER_FRAME;
    scanline %= full_height;
}

void Renderer::RenderFrame(uint8_t* pixels, const Camera& camera, const HittableList& objects) {
    if (low_res) {
        RenderLowRes(pixels, camera, objects);
    } else {
        RenderFullRes(pixels, camera, objects);
    }
}
