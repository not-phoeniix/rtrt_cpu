#include "math_utils.h"

Vec3f Utils::lerp(Vec3f a, Vec3f b, float x) {
    return (b * x) + (a * (1.0f - x));
}

float Utils::lerp(float a, float b, float x) {
    return (b * x) + (a * (1.0f - x));
}

float Utils::randf_range(float min, float max) {
    return min + ((max - min) * ((rand() / (float)RAND_MAX)));
}
