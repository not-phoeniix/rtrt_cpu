#include "hittable.h"

void hit_data_set_face_normal(HitData* hit_data, const Ray& ray, const Vec3f& outward_normal) {
    hit_data->front_face = Vec3f::dot(ray.get_direction(), outward_normal) < 0;
    hit_data->normal = hit_data->front_face ? outward_normal : -outward_normal;
}
