#pragma once

#include "materials/material.h"
#include "thread_pool.h"
#include <stdint.h>
#include "ray.h"
#include "objects/hittable_list.h"
#include "camera.h"

class Renderer {
   private:
    uint32_t full_width;
    uint32_t full_height;
    uint32_t low_res_width;
    uint32_t low_res_height;
    uint32_t writes_per_pixel;
    uint8_t* low_res_pixels;
    float low_res_scale;
    bool low_res;
    ThreadPool thread_pool;
    Vec3f viewport_top_left;
    Vec3f viewport_right;
    Vec3f viewport_down;
    Vec3f pixel_right;
    Vec3f pixel_down;

    void UpdateVectors(const Camera& camera, uint32_t width, uint32_t height);
    Vec3f ShadePixel(const Ray& ray, const HittableList& objects, uint32_t max_depth);
    void RenderBatch(uint32_t i_start, uint32_t count, const Vec3f& cam_pos, uint8_t* pixels, uint32_t width, const HittableList& objects);
    void CopyPixelsBatch(uint32_t i_start, uint32_t count, uint8_t* out_pixels);

    Ray get_ray(uint32_t x, uint32_t y, const Vec3f& cam_pos) const;

    void RenderLowRes(uint8_t* pixels, const Camera& camera, const HittableList& objects);
    void RenderFullRes(uint8_t* pixels, const Camera& camera, const HittableList& objects);

   public:
    Renderer(uint32_t width, uint32_t height, float low_res_scale);
    ~Renderer();

    void set_low_res(bool low_res) { this->low_res = low_res; }

    void RenderFrame(uint8_t* pixels, const Camera& camera, const HittableList& objects);
};
