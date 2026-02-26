#include <iostream>
#include "thirteen.h"
#include <stdint.h>
#include "vec3.h"
#include "vec2.h"
#include "camera.h"
#include "ray.h"
#include "sphere.h"
#include "hittable_list.h"
#include "renderer.h"

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;
constexpr float CAM_SPEED = 3.0f;
constexpr float CAM_LOOK_SPEED = 0.01f;

// returns whether or not something has moved this frame
static bool update_camera(Camera& camera) {
    bool something_moved = false;
    Vec3f pos_offset = {0, 0, 0};

    if (Thirteen::GetKey('w')) {
        pos_offset += camera.get_forward() * CAM_SPEED;
        something_moved = true;
    }
    if (Thirteen::GetKey('s')) {
        pos_offset -= camera.get_forward() * CAM_SPEED;
        something_moved = true;
    }
    if (Thirteen::GetKey('a')) {
        pos_offset -= camera.get_right() * CAM_SPEED;
        something_moved = true;
    }
    if (Thirteen::GetKey('d')) {
        pos_offset += camera.get_right() * CAM_SPEED;
        something_moved = true;
    }
    if (Thirteen::GetKey('e')) {
        pos_offset += {0, CAM_SPEED, 0};
        something_moved = true;
    }
    if (Thirteen::GetKey('q')) {
        pos_offset -= {0, CAM_SPEED, 0};
        something_moved = true;
    }

    Vec3f rot_offset = {0, 0, 0};
    if (Thirteen::GetMouseButton(0)) {
        int x_prev = 0;
        int y_prev = 0;
        int x;
        int y;

        Thirteen::GetMousePosition(x, y);
        Thirteen::GetMousePositionLastFrame(x_prev, y_prev);

        rot_offset.x = (y_prev - y) * CAM_LOOK_SPEED;
        rot_offset.y = (x - x_prev) * CAM_LOOK_SPEED;

        something_moved = true;
    }

    camera.MoveBy(pos_offset * (float)Thirteen::GetDeltaTime());
    camera.RotateBy(rot_offset);

    return something_moved;
}

int main() {
    uint8_t* pixels = Thirteen::Init(WIDTH, HEIGHT);
    if (pixels == nullptr) {
        return 1;
    }

    Camera camera(
        {0, 0, -5},            // pos
        (float)WIDTH / HEIGHT, // aspect
        1.0f,                  // focal length
        2.0f                   // viewport height
    );

    HittableList objects({
        std::make_shared<Sphere>((Vec3f) {0, -1001, 0}, 1000.0f, (Vec3f) {0.1f, 0.1f, 0.1f}),
        std::make_shared<Sphere>((Vec3f) {0, 0, 0}, 1.0f, (Vec3f) {1.0f, 0.25f, 0.25f}),
        // std::make_shared<Sphere>((Vec3f) {-3, 0, 0}, 1.0f, (Vec3f) {0.25f, 1.0f, 0.25f}),
        // std::make_shared<Sphere>((Vec3f) {3, 0, 0}, 1.0f, (Vec3f) {0.25f, 0.25f, 1.0f}),
    });

    Renderer renderer(WIDTH, HEIGHT, 0.25f);

    while (Thirteen::Render() && !Thirteen::GetKey(VK_ESCAPE)) {
        bool something_moved = update_camera(camera);
        renderer.set_low_res(something_moved);
        renderer.RenderFrame(pixels, camera, objects);
    }

    Thirteen::Shutdown();
    return 0;
}
