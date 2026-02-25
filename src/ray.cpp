#include "ray.h"

Ray::Ray(const Vec3f& origin, const Vec3f direction)
  : origin(origin),
    direction(direction) { }

Vec3f Ray::get_at(float x) const { return origin + direction * x; }
const Vec3f& Ray::get_origin() const { return origin; }
const Vec3f& Ray::get_direction() const { return direction; }
