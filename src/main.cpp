#include <iostream>
#include "thirteen.h"
#include <stdint.h>
#include <stdlib.h>
#include "vec3.h"
#include "vec2.h"

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

static float randf_range(float min, float max) {
    return min + ((max - min) * ((rand() / (float)RAND_MAX)));
}

static Vec3f shade(const Vec2f& uv) {
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

    // float dot_value =

    while (Thirteen::Render() && !Thirteen::GetKey(VK_ESCAPE)) {
        for (uint32_t y = 0; y < HEIGHT; y++) {
            for (uint32_t x = 0; x < WIDTH; x++) {
                Vec2f uv = {(float)x / WIDTH, (float)y / HEIGHT};

                Vec3f value = shade(uv);

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
