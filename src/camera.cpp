#include "camera.h"

#include <float.h>
#include <cmath>
#include "math_utils.h"

Camera::Camera(const Vec3f& position, float aspect_ratio, float focal_length, float viewport_height)
  : position(position),
    rotation({0, 0, 0}),
    focal_length(focal_length),
    viewport_height(viewport_height) {
    set_aspect_ratio(aspect_ratio);
}

void Camera::LookAt(const Vec3f& p) {
    Vec3f delta = p - position;
    if (delta.get_length_sq() > FLT_EPSILON) {
        delta = Vec3f::normalize(delta);
    }

    rotation = Utils::get_angles(delta);
}

void Camera::MoveBy(const Vec3f& offset) {
    position += offset;
}

void Camera::RotateBy(const Vec3f& offset) {
    rotation += offset;
}

Vec3f Camera::get_forward() const {
    return Utils::get_forward(rotation.x, rotation.y);
}
Vec3f Camera::get_right() const {
    return Utils::get_right(rotation.y);
}
Vec3f Camera::get_up() const {
    return Utils::get_up(rotation.x, rotation.y);
}

void Camera::set_aspect_ratio(float aspect_ratio) {
    this->aspect_ratio = aspect_ratio;
    viewport_width = viewport_height * aspect_ratio;
}
