#pragma once

#include "vec3.h"

class Camera {
   private:
    Vec3f position;
    // in format "pitch yaw roll"
    Vec3f rotation;
    float aspect_ratio;
    float focal_length;
    float viewport_height;
    float viewport_width;

   public:
    Camera(const Vec3f& position, float aspect_ratio, float focal_length, float viewport_height);

    void LookAt(const Vec3f& pos);
    void MoveBy(const Vec3f& offset);
    void RotateBy(const Vec3f& offset);

    Vec3f get_position() const { return position; }
    float get_aspect_ratio() const { return aspect_ratio; }
    float get_focal_length() const { return focal_length; }
    float get_viewport_width() const { return viewport_width; }
    float get_viewport_height() const { return viewport_height; }
    void set_position(const Vec3f& position) { this->position = position; }
    void set_aspect_ratio(float aspect_ratio);

    Vec3f get_forward() const;
    Vec3f get_right() const;
    Vec3f get_up() const;
};
