#include "lambertian.h"

#include "../math_utils.h"

Lambertian::Lambertian(const Vec3f& albedo)
  : albedo(albedo) { }

bool Lambertian::Scatter(
    const Ray& in_ray,
    const HitData& hit_data,
    Vec3f* out_attenuation,
    Ray* out_scattered
) const {
    Vec3f scatter_dir = hit_data.normal + Utils::get_rand_vec3_norm();
    if (scatter_dir.get_near_zero()) {
        scatter_dir = hit_data.normal;
    }

    *out_scattered = Ray(hit_data.point, scatter_dir);
    *out_attenuation = albedo;
    return true;
}
