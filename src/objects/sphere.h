#pragma once

#include "../vec3.h"
#include "../ray.h"
#include "hittable.h"
#include <memory>
#include "../materials/material.h"

class Sphere : public Hittable {
   private:
    Vec3f center;
    float radius;
    std::shared_ptr<Material> material;

   public:
    Sphere(const Vec3f& center, float radius, std::shared_ptr<Material> material);

    bool Hit(const Ray& ray, const Interval& ray_t, HitData* out_hit_data) const override;
};
