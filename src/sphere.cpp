#include "sphere.h"

Sphere::Sphere(
    const Vec3f& center,
    float radius,
    const Vec3f& color,
    float roughness
) : center(center),
    radius(radius),
    color(color),
    roughness(roughness) { }

float Sphere::CheckHit(const Ray& ray) const {
    Vec3f oc = center - ray.get_origin();
    float a = ray.get_direction().get_length_sq();
    float h = Vec3f::dot(ray.get_direction(), oc);
    float c = oc.get_length_sq() - radius * radius;
    float descriminant = h * h - a * c;

    if (descriminant < 0) {
        return -1.0f;
    } else {
        return (h - std::sqrt(descriminant)) / a;
    }
}
