#include "math_utils.h"

#include <cmath>
#include <float.h>

constexpr uint32_t RAND_SEED = 829734215;

Vec3f Utils::lerp(Vec3f a, Vec3f b, float x) {
    return (b * x) + (a * (1.0f - x));
}

float Utils::lerp(float a, float b, float x) {
    return (b * x) + (a * (1.0f - x));
}

float Utils::randf_range(float min, float max) {
    // xorshift for random that is way faster than built-in cstdlib
    //   https://en.wikipedia.org/wiki/Xorshift
    static uint32_t state = RAND_SEED;

    uint32_t x = state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    state = x;

    return min + ((max - min) * ((float)x / (float)UINT32_MAX));
}

Vec3f Utils::get_rand_vec3(float min, float max) {
    return {
        randf_range(min, max),
        randf_range(min, max),
        randf_range(min, max)
    };
}

Vec3f Utils::get_rand_vec3_norm() {
    while (true) {
        Vec3f p = get_rand_vec3(-1, 1);
        float len_sq = p.get_length_sq();
        if (len_sq >= FLT_EPSILON && len_sq <= 1.0f) {
            return p / std::sqrtf(len_sq);
        }
    }
}

Vec3f Utils::get_rand_vec3_on_hemisphere(const Vec3f& normal) {
    // avoid branching to reduce CPU cache misses
    Vec3f on_unit_sphere = get_rand_vec3_norm();
    bool invert = Vec3f::dot(on_unit_sphere, normal) < 0.0f;
    on_unit_sphere *= ((float)invert * -1.0f) + ((float)(!invert) * 1.0f);
    return on_unit_sphere;
}

// equations grabbed from:
// https://gamedev.stackexchange.com/questions/190054/how-to-calculate-the-forward-up-right-vectors-using-the-rotation-angles

Vec3f Utils::get_forward(float pitch, float yaw) {
    float x = std::cosf(pitch) * std::sinf(yaw);
    float y = std::sinf(pitch);
    float z = std::cosf(pitch) * std::cosf(yaw);

    return {x, y, z};
}

Vec3f Utils::get_right(float yaw) {
    float x = std::cosf(yaw);
    float y = 0.0f;
    float z = -std::sinf(yaw);

    return {x, y, z};
}

Vec3f Utils::get_up(float pitch, float yaw) {
    Vec3f forward = get_forward(pitch, yaw);
    Vec3f right = get_right(yaw);
    return Vec3f::cross(forward, right);
}

Vec3f Utils::get_angles(Vec3f forward) {
    float yaw = std::atan2f(forward.x, forward.z);
    float pitch = std::asin(-forward.y);

    return {pitch, yaw, 0};
}

float Utils::correct_gamma(float value) {
    if (value > 0.0f) {
        return std::sqrtf(value);
    }

    return 0.0f;
}
