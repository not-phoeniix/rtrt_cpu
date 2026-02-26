#pragma once

#include "../vec3.h"
#include "../ray.h"
#include "hittable.h"

class Sphere : public Hittable {
   private:
    Vec3f center;
    float radius;
    Vec3f color;

   public:
    Sphere(const Vec3f& center, float radius, const Vec3f& color);

    bool Hit(const Ray& ray, const Interval& ray_t, HitData* out_hit_data) const override;

    const Vec3f& get_color() const { return color; }
    const Vec3f& get_center() const { return center; }
};
