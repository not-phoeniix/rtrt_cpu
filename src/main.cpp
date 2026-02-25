#include <iostream>
#include "thirteen.h"
#include <stdint.h>
#include <stdlib.h>
#include "vec3.h"
#include "vec2.h"
#include "camera.h"
#include "ray.h"

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

static float randf_range(float min, float max) {
    return min + ((max - min) * ((rand() / (float)RAND_MAX)));
}

static Vec3f shade(const Vec2f& uv, const Ray& ray) {
    return (Vec3f) {uv.x, uv.y, 0.0f};

    // return (Vec3f) {
    //     randf_range(0.0f, 1.0f),
    //     randf_range(0.0f, 1.0f),
    //     randf_range(0.0f, 1.0f)
    // };
}

int main() {
    srand((unsigned int)time(NULL));

    uint8_t* pixels = Thirteen::Init(WIDTH, HEIGHT);
    if (pixels == nullptr) {
        return 1;
    }

    Camera camera(
        {0, 0, -10},           // pos
        (float)WIDTH / HEIGHT, // aspect
        65.0f * M_PI / 180.0f, // fov
        0.01f                  // near plane
    );

    float viewport_width = camera.get_viewport_width();
    float viewport_height = camera.get_viewport_height();

    float pixel_width = viewport_width / WIDTH;
    float pixel_height = viewport_height / HEIGHT;

    while (Thirteen::Render() && !Thirteen::GetKey(VK_ESCAPE)) {
        Vec3f cam_pos = camera.get_position();

        Vec3f top_left = cam_pos + (camera.get_viewport_tl_dir() * camera.get_near_plane());
        Vec3f right = camera.get_right();
        Vec3f down = -camera.get_up();

        for (uint32_t y = 0; y < HEIGHT; y++) {
            for (uint32_t x = 0; x < WIDTH; x++) {
                Vec3f frag_screen_pos = top_left +
                                        (right * (pixel_width * x)) +
                                        (down * (pixel_height * y));
                Vec3f ray_dir = frag_screen_pos - cam_pos;
                Ray ray(cam_pos, ray_dir);

                Vec2f uv = {(float)x / WIDTH, (float)y / HEIGHT};

                Vec3f value = shade(uv, ray);

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
