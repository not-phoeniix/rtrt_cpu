#include "hittable_list.h"

HittableList::HittableList(std::shared_ptr<Hittable> object) {
    Add(object);
}

HittableList::HittableList(const std::vector<std::shared_ptr<Hittable>>& objects)
  : objects(objects) { }

void HittableList::Add(std::shared_ptr<Hittable> object) {
    objects.push_back(object);
}

bool HittableList::Hit(const Ray& ray, float ray_tmin, float ray_tmax, HitData* out_hit) const {
    bool hit_anything = false;
    HitData tmp_data;
    float t_closest = ray_tmax;

    for (const auto& object : objects) {
        if (object->Hit(ray, ray_tmin, ray_tmax, &tmp_data)) {
            hit_anything = true;
            t_closest = tmp_data.t;
            *out_hit = tmp_data;
        }
    }

    return hit_anything;
}
