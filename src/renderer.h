#pragma once

#include "thread_pool.h"
#include <stdint.h>
#include "ray.h"
#include "hittable_list.h"
#include "camera.h"

class Renderer {
   private:
    uint32_t width;
    uint32_t height;
    ThreadPool thread_pool;
    Vec3f viewport_top_left;
    Vec3f viewport_right;
    Vec3f viewport_down;
    Vec3f pixel_right;
    Vec3f pixel_down;

    Vec3f ShadePixel(const Ray& ray, const HittableList& objects);
    void RenderBatch(uint32_t i_start, uint32_t count, const Vec3f& cam_pos, uint8_t* pixels, const HittableList& objects);

    Ray get_ray(uint32_t x, uint32_t y, const Vec3f& cam_pos) const;

   public:
    Renderer(uint32_t width, uint32_t height);

    void RenderFrame(uint8_t* pixels, const Camera& camera, const HittableList& objects);
};
