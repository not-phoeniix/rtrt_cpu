#pragma once

#include "vec3.h"

Vec3f rot_get_forward(float pitch, float yaw);
Vec3f rot_get_right(float yaw);
Vec3f rot_get_up(float pitch, float yaw);
Vec3f rot_get_angles(Vec3f forward);
