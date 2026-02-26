#pragma once

#include "vec3.h"

namespace Utils {
    Vec3f lerp(Vec3f a, Vec3f b, float x);
    float lerp(float a, float b, float x);
    float randf_range(float min, float max);
    Vec3f get_forward(float pitch, float yaw);
    Vec3f get_right(float yaw);
    Vec3f get_up(float pitch, float yaw);
    Vec3f get_angles(Vec3f forward);
};
