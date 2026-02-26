#pragma once

#include "../ray.h"
#include "../vec3.h"
#include "../interval.h"
#include <memory>

class Material;

struct HitData {
    Vec3f point;
    Vec3f normal;
    std::shared_ptr<Material> material;
    float t;
    bool front_face;
};

void hit_data_set_face_normal(HitData* hit_data, const Ray& ray, const Vec3f& outward_normal);

class Hittable {
   public:
    virtual ~Hittable() = default;
    virtual bool Hit(const Ray& ray, const Interval& ray_t, HitData* out_hit) const = 0;
};
