#include "renderer.h"

#include "math_utils.h"
#include "interval.h"

Renderer::Renderer(uint32_t width, uint32_t height)
  : width(width),
    height(height) {
}

Vec3f Renderer::ShadePixel(const Ray& ray, const HittableList& objects) {
    HitData hit_data;
    if (objects.Hit(ray, Interval(0, INFINITY_F), &hit_data)) {
        return hit_data.normal * 0.5f + (Vec3f) {0.5f, 0.5f, 0.5f};
    }

    Vec3f dir_norm = Vec3f::normalize(ray.get_direction());
    float a = 0.5f * (dir_norm.y + 1.0f);
    return Utils::lerp({1.0f, 1.0f, 1.0f}, {0.5f, 0.7f, 1.0f}, a);
}

void Renderer::RenderBatch(uint32_t i_start, uint32_t count, const Vec3f& cam_pos, uint8_t* pixels, const HittableList& objects) {
    for (uint32_t i = i_start; i < i_start + count; i++) {
        uint32_t y = i / width;
        uint32_t x = i - (y * width);

        Vec3f frag_screen_pos = viewport_top_left + (pixel_right * (float)x) + (pixel_down * (float)y);
        Vec3f ray_dir = frag_screen_pos - cam_pos;

        Ray ray(cam_pos, ray_dir);

        Vec3f value = ShadePixel(ray, objects);

        static const Interval intensity(0.0f, 1.0f);
        pixels[i * 4 + 0] = (uint8_t)(intensity.Clamp(value.x) * 255.0f);
        pixels[i * 4 + 1] = (uint8_t)(intensity.Clamp(value.y) * 255.0f);
        pixels[i * 4 + 2] = (uint8_t)(intensity.Clamp(value.z) * 255.0f);
        pixels[i * 4 + 3] = 255;
    }
}

void Renderer::RenderFrame(uint8_t* pixels, const Camera& camera, const HittableList& objects) {
    Vec3f cam_pos = camera.get_position();

    viewport_right = camera.get_right() * camera.get_viewport_width();
    viewport_down = -camera.get_up() * camera.get_viewport_height();
    pixel_right = viewport_right / (float)width;
    pixel_down = viewport_down / (float)height;
    viewport_top_left = cam_pos +
                        camera.get_forward() * camera.get_focal_length() -
                        (viewport_right / 2.0f) -
                        (viewport_down / 2.0f);
    viewport_top_left += (pixel_right * 0.5f);
    viewport_top_left += (pixel_down * 0.5f);

    // send shading in grouped-together batches
    //   if we send them off all scattered then cache misses
    //   will cause serious performance hits

    uint32_t pixel_index_start = 0;
    uint32_t pixels_remaining = width * height;

    for (uint32_t i = 0; i < thread_pool.get_thread_count(); i++) {
        uint32_t count = width * height / thread_pool.get_thread_count();
        if (count > pixels_remaining) count = pixels_remaining;

        thread_pool.QueueJob([=](uint32_t thread_index) {
            RenderBatch(pixel_index_start, count, cam_pos, pixels, objects);
        });

        pixel_index_start += count;
        pixels_remaining -= count;
    }

    thread_pool.Wait();
}
