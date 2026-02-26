#pragma once

#include "material.h"

class Metal : public Material {
   private:
    Vec3f albedo;
    float fuzz;

   public:
    Metal(const Vec3f& albedo, float fuzz);

    bool Scatter(
        const Ray& in_ray,
        const HitData& hit_data,
        Vec3f* out_attenuation,
        Ray* out_scattered
    ) const override;
};
