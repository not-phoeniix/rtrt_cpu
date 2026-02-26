#pragma once

#include "ray.h"
#include "vec3.h"

struct HitData {
    Vec3f point;
    Vec3f normal;
    float t;
    bool front_face;
};

void hit_data_set_face_normal(HitData* hit_data, const Ray& ray, const Vec3f& outward_normal);

class Hittable {
   public:
    virtual ~Hittable() = default;
    virtual bool Hit(const Ray& ray, float ray_tmin, float ray_tmax, HitData* out_hit) const = 0;
};
