#pragma once

#include "ray.h"
#include "hittable.h"

class Material {
    virtual ~Material() = default;

    virtual bool Scatter(
        const Ray& in_ray,
        const HitData& hit_data,
        Vec3f* out_attenuation,
        Ray* out_scattered
    ) const { return false; }
};
