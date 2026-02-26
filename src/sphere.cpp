#include "sphere.h"

Sphere::Sphere(
    const Vec3f& center,
    float radius,
    const Vec3f& color
) : center(center),
    radius(std::fmaxf(radius, 0.0f)),
    color(color) { }

bool Sphere::Hit(const Ray& ray, float ray_tmin, float ray_tmax, HitData* out_hit_data) const {
    Vec3f oc = center - ray.get_origin();
    float a = ray.get_direction().get_length_sq();
    float h = Vec3f::dot(ray.get_direction(), oc);
    float c = oc.get_length_sq() - radius * radius;

    float descriminant = h * h - a * c;
    if (descriminant < 0) {
        return false;
    }

    float sqrt_d = std::sqrt(descriminant);

    // find the nearest root that lies within acceptable range
    float root = (h - sqrt_d) / a;
    if (root <= ray_tmin || root >= ray_tmax) {
        root = (h + sqrt_d) / a;
        if (root <= ray_tmin || root >= ray_tmax) {
            return false;
        }
    }

    out_hit_data->t = root;
    out_hit_data->point = ray.get_at(root);
    Vec3f outward_normal = (out_hit_data->point - center) / radius;
    hit_data_set_face_normal(out_hit_data, ray, outward_normal);

    return true;
}
