#pragma once

#include "material.h"

class Lambertian : public Material {
   private:
    Vec3f albedo;

   public:
    Lambertian(const Vec3f& albedo);

    bool Scatter(
        const Ray& in_ray,
        const HitData& hit_data,
        Vec3f* out_attenuation,
        Ray* out_scattered
    ) const override;
};
