#include "camera.h"

#include <float.h>
#include <cmath>
#include "rot_helpers.h"

Camera::Camera(const Vec3f& position, float aspect_ratio, float fovy, float near_plane)
  : position(position),
    rotation({0, 0, 0}),
    fovy(fovy),
    near_plane(near_plane) {
    // use helper function so fovx is also set
    set_aspect_ratio(aspect_ratio);
}

void Camera::LookAt(const Vec3f& p) {
    Vec3f delta = p - position;
    if (delta.get_length_sq() > FLT_EPSILON) {
        delta = Vec3f::normalize(delta);
    }

    rotation = rot_get_angles(delta);
}

void Camera::MoveBy(const Vec3f& offset) {
    position += offset;
}

void Camera::RotateBy(const Vec3f& offset) {
    rotation += offset;
}

Vec3f Camera::get_forward() const {
    return rot_get_forward(rotation.x, rotation.y);
}
Vec3f Camera::get_right() const {
    return rot_get_right(rotation.y);
}
Vec3f Camera::get_up() const {
    return rot_get_up(rotation.x, rotation.y);
}

void Camera::set_aspect_ratio(float aspect_ratio) {
    this->aspect_ratio = aspect_ratio;
    // https://en.wikipedia.org/wiki/Field_of_view_in_video_games
    fovx = 2.0f * std::atanf(aspect_ratio * std::tanf(fovy / 2.0f));
}

Vec3f Camera::get_viewport_tl_dir() const {
    return rot_get_forward(
        rotation.x + (fovy / 2.0f),
        rotation.y - (fovx / 2.0f)
    );
}

Vec3f Camera::get_viewport_br_dir() const {
    return rot_get_forward(
        rotation.x - (fovy / 2.0f),
        rotation.y + (fovx / 2.0f)
    );
}

float Camera::get_viewport_width() const {
    Vec3f tl_dir = rot_get_forward(fovy / 2.0f, -fovx / 2.0f);
    Vec3f br_dir = rot_get_forward(-fovy / 2.0f, fovx / 2.0f);

    Vec3f tl_plane = tl_dir * near_plane;
    Vec3f br_plane = br_dir * near_plane;

    return br_plane.x - tl_plane.x;
}

float Camera::get_viewport_height() const {
    Vec3f tl_dir = rot_get_forward(fovy / 2.0f, -fovx / 2.0f);
    Vec3f br_dir = rot_get_forward(-fovy / 2.0f, fovx / 2.0f);

    Vec3f tl_plane = tl_dir * near_plane;
    Vec3f br_plane = br_dir * near_plane;

    return tl_plane.y - br_plane.y;
}
