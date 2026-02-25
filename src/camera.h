#pragma once

#include "vec3.h"

class Camera {
   private:
    Vec3f position;
    // in format "pitch yaw roll"
    Vec3f rotation;
    float aspect_ratio;
    float fov;
    float near_plane;

   public:
    Camera(const Vec3f& position, float aspect_ratio, float fov, float near_plane);

    void LookAt(const Vec3f& pos);
    Vec3f get_forward() const;
    Vec3f get_right() const;
    Vec3f get_up() const;

    inline static Vec3f get_directional(float pitch, float yaw);
};
