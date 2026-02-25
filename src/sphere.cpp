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
    float a = Vec3f::dot(ray.get_direction(), ray.get_direction());
    float b = -2.0f * Vec3f::dot(ray.get_direction(), oc);
    float c = Vec3f::dot(oc, oc) - (radius * radius);
    float descriminant = b * b - 4 * a * c;

    if (descriminant < 0) {
        return -1.0f;
    } else {
        return (-b - std::sqrtf(descriminant)) / (2.0f * a);
    }
}
