#include "math_utils.h"

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
