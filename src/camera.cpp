#include "camera.h"

#include <float.h>
#include <cmath>

Camera::Camera(const Vec3f& position, float aspect_ratio, float fov, float near_plane)
  : position(position),
    rotation({0, 0, 0}),
    aspect_ratio(aspect_ratio),
    fov(fov),
    near_plane(near_plane) { }

void Camera::LookAt(const Vec3f& p) {
    Vec3f delta = p - position;
    if (delta.get_length_sq() > FLT_EPSILON) {
        delta = Vec3f::normalize(delta);
    }

    float yaw = std::atan2f(delta.x, delta.z);
    float pitch = std::asin(-delta.y);

    rotation = {pitch, yaw, 0};
}

Vec3f Camera::get_forward() const {
    return get_directional(rotation.x, rotation.y);
}

Vec3f Camera::get_right() const {
    return get_directional(rotation.x, rotation.y + M_PI_2);
}

Vec3f Camera::get_up() const {
    return get_directional(rotation.x + M_PI_2, rotation.y);
}

inline Vec3f Camera::get_directional(float pitch, float yaw) {
    // https://stackoverflow.com/questions/1568568/how-to-convert-euler-angles-to-directional-vector
    // if x is forward and z is up,,,
    // x = cos(yaw)*cos(pitch)
    // y = sin(yaw)*cos(pitch)
    // z = sin(pitch)

    float z = std::cosf(yaw) * std::cosf(pitch);
    float x = std::sinf(yaw) * std::cosf(pitch);
    float y = std::sinf(pitch);

    return {x, y, z};
}
