#pragma once

#include "vec3.h"

class Camera {
   private:
    Vec3f position;
    // in format "pitch yaw roll"
    Vec3f rotation;
    float aspect_ratio;
    float fovy;
    float fovx;
    float near_plane;

   public:
    Camera(const Vec3f& position, float aspect_ratio, float fovy, float near_plane);

    void LookAt(const Vec3f& pos);
    void MoveBy(const Vec3f& offset);
    void RotateBy(const Vec3f& offset);

    Vec3f get_position() const { return position; }
    float get_aspect_ratio() const { return aspect_ratio; }
    float get_near_plane() const { return near_plane; }
    void set_position(const Vec3f& position) { this->position = position; }
    void set_aspect_ratio(float aspect_ratio);

    float get_fovy() const { return fovy; }
    float get_fovx() const { return fovx; }

    Vec3f get_forward() const;
    Vec3f get_right() const;
    Vec3f get_up() const;

    Vec3f get_viewport_tl_dir() const;
    Vec3f get_viewport_br_dir() const;
    float get_viewport_width() const;
    float get_viewport_height() const;
};
