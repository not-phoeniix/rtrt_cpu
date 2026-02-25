#include "rot_helpers.h"

// equations grabbed from:
// https://gamedev.stackexchange.com/questions/190054/how-to-calculate-the-forward-up-right-vectors-using-the-rotation-angles

Vec3f rot_get_forward(float pitch, float yaw) {
    float x = std::cosf(pitch) * std::sinf(yaw);
    float y = std::sinf(pitch);
    float z = std::cosf(pitch) * std::cosf(yaw);

    return {x, y, z};
}

Vec3f rot_get_right(float yaw) {
    float x = std::cosf(yaw);
    float y = 0.0f;
    float z = -std::sinf(yaw);

    return {x, y, z};
}

Vec3f rot_get_up(float pitch, float yaw) {
    Vec3f forward = rot_get_forward(pitch, yaw);
    Vec3f right = rot_get_right(yaw);
    return Vec3f::cross(forward, right);
}

Vec3f rot_get_angles(Vec3f forward) {
    float yaw = std::atan2f(forward.x, forward.z);
    float pitch = std::asin(-forward.y);

    return {pitch, yaw, 0};
}
