#include <iostream>
#include "thirteen.h"
#include <stdint.h>
#include <stdlib.h>
#include "vec3.h"
#include "vec2.h"
#include "camera.h"
#include "ray.h"
#include "sphere.h"
#include "hittable_list.h"

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;
constexpr float CAM_SPEED = 2.0f;
constexpr float CAM_LOOK_SPEED = 0.1f;

static float randf_range(float min, float max) {
    return min + ((max - min) * ((rand() / (float)RAND_MAX)));
}

static float lerp(float a, float b, float x) {
    return (b * x) + (a * (1.0f - x));
}

static Vec3f lerp(Vec3f a, Vec3f b, float x) {
    return (b * x) + (a * (1.0f - x));
}

static HittableList objects({
    std::make_shared<Sphere>((Vec3f) {0, 0, 0}, 1.0f, (Vec3f) {1.0f, 0.25f, 0.25f}),
    std::make_shared<Sphere>((Vec3f) {-3, 0, 0}, 1.0f, (Vec3f) {0.25f, 1.0f, 0.25f}),
    std::make_shared<Sphere>((Vec3f) {3, 0, 0}, 1.0f, (Vec3f) {0.25f, 0.25f, 1.0f}),
});

static void update_camera(Camera& camera) {
    Vec3f pos_offset = {0, 0, 0};

    if (Thirteen::GetKey('w')) pos_offset += camera.get_forward() * CAM_SPEED;
    if (Thirteen::GetKey('s')) pos_offset -= camera.get_forward() * CAM_SPEED;
    if (Thirteen::GetKey('a')) pos_offset -= camera.get_right() * CAM_SPEED;
    if (Thirteen::GetKey('d')) pos_offset += camera.get_right() * CAM_SPEED;
    if (Thirteen::GetKey('e')) pos_offset += {0, CAM_SPEED, 0};
    if (Thirteen::GetKey('q')) pos_offset -= {0, CAM_SPEED, 0};

    Vec3f rot_offset = {0, 0, 0};
    if (Thirteen::GetMouseButton(0)) {
        int x_prev = 0;
        int y_prev = 0;
        int x;
        int y;

        Thirteen::GetMousePosition(x, y);
        Thirteen::GetMousePositionLastFrame(x_prev, y_prev);

        rot_offset.x = (y_prev - y) * CAM_LOOK_SPEED;
        rot_offset.y = (x - x_prev) * CAM_LOOK_SPEED;
    }

    camera.MoveBy(pos_offset * (float)Thirteen::GetDeltaTime());
    camera.RotateBy(rot_offset * (float)Thirteen::GetDeltaTime());
}

static Vec3f shade(const Ray& ray) {
    HitData hit_data;
    if (objects.Hit(ray, 0.0, 10000.0f, &hit_data)) {
        return hit_data.normal * 0.5f + (Vec3f) {0.5f, 0.5f, 0.5f};
    }

    Vec3f dir_norm = Vec3f::normalize(ray.get_direction());
    float a = 0.5f * (dir_norm.y + 1.0f);
    return lerp({1.0f, 1.0f, 1.0f}, {0.5f, 0.7f, 1.0f}, a);
}

int main() {
    srand((unsigned int)time(NULL));

    uint8_t* pixels = Thirteen::Init(WIDTH, HEIGHT);
    if (pixels == nullptr) {
        return 1;
    }

    Camera camera(
        {0, 0, -5},            // pos
        (float)WIDTH / HEIGHT, // aspect
        1.0f,                  // focal length
        2.0f                   // viewport height
    );

    while (Thirteen::Render() && !Thirteen::GetKey(VK_ESCAPE)) {
        update_camera(camera);

        Vec3f cam_pos = camera.get_position();

        Vec3f viewport_right = camera.get_right() * camera.get_viewport_width();
        Vec3f viewport_down = -camera.get_up() * camera.get_viewport_height();
        Vec3f pixel_right = viewport_right / (float)WIDTH;
        Vec3f pixel_down = viewport_down / (float)HEIGHT;
        Vec3f top_left = cam_pos +
                         camera.get_forward() * camera.get_focal_length() -
                         (viewport_right / 2.0f) -
                         (viewport_down / 2.0f);
        top_left += (pixel_right * 0.5f);
        top_left += (pixel_down * 0.5f);

        for (uint32_t y = 0; y < HEIGHT; y++) {
            for (uint32_t x = 0; x < WIDTH; x++) {
                Vec3f frag_screen_pos = top_left + (pixel_right * (float)x) + (pixel_down * (float)y);
                Vec3f ray_dir = frag_screen_pos - cam_pos;

                Ray ray(cam_pos, ray_dir);

                Vec3f value = shade(ray);

                uint8_t* pixel = &pixels[(y * 4 * WIDTH) + (x * 4)];
                pixel[0] = static_cast<uint8_t>(value.x * 255.0f);
                pixel[1] = static_cast<uint8_t>(value.y * 255.0f);
                pixel[2] = static_cast<uint8_t>(value.z * 255.0f);
                pixel[3] = 255;
            }
        }
    }

    Thirteen::Shutdown();
    return 0;
}
