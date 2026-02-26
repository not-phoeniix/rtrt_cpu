#pragma once

#include "vec3.h"

namespace Utils {
    Vec3f lerp(Vec3f a, Vec3f b, float x);
    float lerp(float a, float b, float x);
    float randf_range(float min, float max);
    Vec3f get_rand_vec3(float min, float max);
    Vec3f get_rand_vec3_norm();
    Vec3f get_rand_vec3_on_hemisphere(const Vec3f& normal);
    Vec3f get_forward(float pitch, float yaw);
    Vec3f get_right(float yaw);
    Vec3f get_up(float pitch, float yaw);
    Vec3f get_angles(Vec3f forward);
    float correct_gamma(float value);
};
