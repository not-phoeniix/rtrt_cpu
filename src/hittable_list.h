#pragma once

#include "hittable.h"
#include <vector>
#include <memory>

class HittableList : public Hittable {
   private:
    std::vector<std::shared_ptr<Hittable>> objects;

   public:
    HittableList() = default;
    HittableList(std::shared_ptr<Hittable> object);
    HittableList(const std::vector<std::shared_ptr<Hittable>>& objects);

    void Add(std::shared_ptr<Hittable> object);

    bool Hit(const Ray& ray, float ray_tmin, float ray_tmax, HitData* out_hit) const override;
};
