#pragma once

#include "vec3.h"
#include "ray.h"

class Sphere {
   private:
    Vec3f center;
    float radius;
    Vec3f color;
    float roughness;

   public:
    Sphere(const Vec3f& center, float radius, const Vec3f& color, float roughness);

    bool Intersects(const Ray& ray) const;

    const Vec3f& get_color() const { return color; }
};
