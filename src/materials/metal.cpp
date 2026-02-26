#include "metal.h"

#include <cstdlib>
#include "../math_utils.h"

Metal::Metal(const Vec3f& albedo, float fuzz)
  : albedo(albedo),
    fuzz(std::min(fuzz, 1.0f)) { }

bool Metal::Scatter(const Ray& in_ray, const HitData& hit_data, Vec3f* out_attenuation, Ray* out_scattered) const {
    Vec3f refl = Vec3f::reflect(in_ray.get_direction(), hit_data.normal);
    refl = Vec3f::normalize(refl) + (Utils::get_rand_vec3_norm() * fuzz);
    *out_scattered = Ray(hit_data.point, refl);
    *out_attenuation = albedo;
    return (Vec3f::dot(out_scattered->get_direction(), hit_data.normal) > 0.0f);
}
