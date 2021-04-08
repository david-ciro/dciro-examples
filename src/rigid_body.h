#ifndef rigid_body_H
#define rigid_body_H

#include "stdlib.h"

typedef struct rigid_body_h* rigid_body;

typedef enum
{
    // the total mass
    rgb_m,
    // the inertia tensor (resp. C.M.)
    rgb_Ixx,
    rgb_Ixy, // Iyx
    rgb_Ixz, // Izx
    rgb_Iyy,
    rgb_Iyz, // Izy
    rgb_Izz,
    // the center of mass
    rgb_x,
    rgb_y,
    rgb_z,
    // center of mass velocity
    rgb_vx,
    rgb_vy,
    rgb_vz,
    // angular velocity about main axes
    rgb_wx,
    rgb_wy,
    rgb_wz
}
rgb_param;

rigid_body
rgb_create();

void
rgb_destroy(rigid_body rgb);

void
rgb_set_param(rigid_body rgb, rgb_param name, double value);

double
rgb_get_param(rigid_body rgb, rgb_param name);

// regular setters and getters
void
rgb_set_m(rigid_body rgb, double m);

double
rgb_get_m(rigid_body rgb);

void
rgb_set_Iij(rigid_body rgb, size_t i, size_t j, double Iij);

double
rgb_get_Iij(rigid_body rgb, size_t i, size_t j);

void
rgb_set_xi(rigid_body rgb, size_t i, double xi);

double
rgb_get_xi(rigid_body rgb, size_t i);

void
rgb_set_vi(rigid_body rgb, size_t i, double vi);

double
rgb_get_vi(rigid_body rgb, size_t i);

void
rgb_set_wi(rigid_body rgb, size_t i, double wi);

double
rgb_get_wi(rigid_body rgb, size_t i);

#endif // rigid_body_H