#include "sphere.h"

Sphere::Sphere(
    const Vec3f& center,
    float radius,
    std::shared_ptr<Material> material
) : center(center),
    radius(std::fmaxf(radius, 0.0f)),
    material(material) { }

bool Sphere::Hit(const Ray& ray, const Interval& ray_t, HitData* out_hit_data) const {
    Vec3f oc = center - ray.get_origin();
    float a = Vec3f::length_sq(ray.get_direction());
    float h = Vec3f::dot(ray.get_direction(), oc);
    float c = Vec3f::length_sq(oc) - radius * radius;

    float descriminant = h * h - a * c;
    if (descriminant < 0) {
        return false;
    }

    float sqrt_d = std::sqrt(descriminant);

    // find the nearest root that lies within acceptable range
    float root = (h - sqrt_d) / a;
    if (!ray_t.Surrounds(root)) {
        root = (h + sqrt_d) / a;
        if (!ray_t.Surrounds(root)) {
            return false;
        }
    }

    out_hit_data->t = root;
    out_hit_data->point = ray.get_at(root);
    out_hit_data->material = material;
    Vec3f outward_normal = (out_hit_data->point - center) / radius;
    hit_data_set_face_normal(out_hit_data, ray, outward_normal);

    return true;
}
