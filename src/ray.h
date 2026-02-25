#include "vec3.h"

class Ray {
   private:
    Vec3f origin;
    Vec3f direction;

   public:
    Ray(const Vec3f& origin, const Vec3f direction);

    Vec3f get_at(float x);
    const Vec3f& get_origin() const;
    const Vec3f& get_direction() const;
};
