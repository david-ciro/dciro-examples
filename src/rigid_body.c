#include "rigid_body.h"
#include <math.h>
#include <stdio.h>

typedef struct
{
    double  m;
    double* I; // {Ixx, Iyy, Izz, Ixy, Ixz, Iyz}
    double* x; // {x, y, z}
    double* v; // {vx, vy, vz}
    double* w; // {wx, wy, wz}
    // other params
} rigid_body_t;

rigid_body
rgb_create()
{
    rigid_body_t* rgb = (rigid_body_t*)malloc(sizeof(rigid_body_t));
    rgb->I = (double*)malloc(6 * sizeof(double));
    rgb->x = (double*)malloc(3 * sizeof(double));
    rgb->v = (double*)malloc(3 * sizeof(double));
    rgb->w = (double*)malloc(3 * sizeof(double));
    return (rigid_body)rgb;
}

void
rgb_destroy(rigid_body rgb_h)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    free(rgb->I);
    free(rgb->x);
    free(rgb->v);
    free(rgb->w);
}

void
rgb_set_param(rigid_body rgb_h, rgb_param name, double value)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    switch (name) {
        case rgb_m:
            if (value > 0)
                rgb->m = value;
            else
                fprintf(stderr, "rgb_set_param: invalid mass\n");
            break;

        case rgb_Ixx:
            if (value > 0)
                rgb->I[0] = value;
            else
                fprintf(stderr, "rgb_set_param: invalid Ixx\n");
            break;

        case rgb_Iyy:
            if (value > 0)
                rgb->I[1] = value;
            else
                fprintf(stderr, "rgb_set_param: invalid Iyy\n");
            break;

        case rgb_Izz:
            if (value > 0)
                rgb->I[2] = value;
            else
                fprintf(stderr, "rgb_set_param: invalid Izz\n");
            break;

        case rgb_Ixy:
            rgb->I[3] = value;
            break;

        case rgb_Ixz:
            rgb->I[4] = value;
            break;

        case rgb_Iyz:
            rgb->I[5] = value;
            break;

        case rgb_x:
            rgb->x[0] = value;
            break;

        case rgb_y:
            rgb->x[1] = value;
            break;

        case rgb_z:
            rgb->x[2] = value;
            break;

        case rgb_vx:
            rgb->v[0] = value;
            break;

        case rgb_vy:
            rgb->v[1] = value;
            break;

        case rgb_vz:
            rgb->v[2] = value;
            break;

        case rgb_wx:
            rgb->w[0] = value;
            break;

        case rgb_wy:
            rgb->w[1] = value;
            break;

        case rgb_wz:
            rgb->w[2] = value;
            break;

        default:
            fprintf(stderr, "rgb_set_param: unknown param name\n");
            break;
    }
}

double
rgb_get_param(rigid_body rgb_h, rgb_param name)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    switch (name) {
        case rgb_m:
            return rgb->m;

        case rgb_Ixx:
            return rgb->I[0];

        case rgb_Iyy:
            return rgb->I[1];

        case rgb_Izz:
            return rgb->I[2];

        case rgb_Ixy:
            return rgb->I[3];

        case rgb_Ixz:
            return rgb->I[4];

        case rgb_Iyz:
            return rgb->I[5];

        case rgb_x:
            return rgb->x[0];

        case rgb_y:
            return rgb->x[1];

        case rgb_z:
            return rgb->x[2];

        case rgb_vx:
            return rgb->v[0];

        case rgb_vy:
            return rgb->v[1];

        case rgb_vz:
            return rgb->v[2];

        case rgb_wx:
            return rgb->w[0];

        case rgb_wy:
            return rgb->w[1];

        case rgb_wz:
            return rgb->w[2];

        default:
            fprintf(stderr, "rgb_get_param: unknown param name\n");
            return NAN;
    }
}

void
rgb_set_m(rigid_body rgb_h, double m)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    if (m > 0)
        rgb->m = m;
    else
        fprintf(stderr, "rgb_set_param: invalid mass\n");
}

double
rgb_get_m(rigid_body rgb_h)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    return rgb->m;
}

void
rgb_set_Iij(rigid_body rgb_h, size_t i, size_t j, double Iij)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    if (i > 3 || j > 3)
        fprintf(stderr, "rgb_get_Iij: invalid index\n");
    if (i == j) {
        if (Iij > 0)
            rgb->I[i] = Iij;
        else
            fprintf(stderr, "rgb_get_Iij: invalid value\n");
    } else
        rgb->I[i + j + 2] = Iij;
}

double
rgb_get_Iij(rigid_body rgb_h, size_t i, size_t j)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    if (i > 3 || j > 3)
        fprintf(stderr, "rgb_get_Iij: invalid index\n");
    if (i == j)
        return rgb->I[i];
    else
        return rgb->I[i + j + 2];
}

void
rgb_set_xi(rigid_body rgb_h, size_t i, double xi)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    if (i < 3)
        rgb->x[i] = xi;
    else
        fprintf(stderr, "rgb_set_xi: invalid index\n");
}

double
rgb_get_xi(rigid_body rgb_h, size_t i)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    if (i < 3)
        return rgb->x[i];
    else {
        fprintf(stderr, "rgb_get_xi: invalid index\n");
        return NAN;
    }
}

void
rgb_set_vi(rigid_body rgb_h, size_t i, double vi)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    if (i < 3)
        rgb->v[i] = vi;
    else
        fprintf(stderr, "rgb_set_vi: invalid index\n");
}

double
rgb_get_vi(rigid_body rgb_h, size_t i)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    if (i < 3)
        return rgb->v[i];
    else {
        fprintf(stderr, "rgb_get_vi: invalid index\n");
        return NAN;
    }
}

void
rgb_set_wi(rigid_body rgb_h, size_t i, double wi)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    if (i < 3)
        rgb->w[i] = wi;
    else
        fprintf(stderr, "rgb_set_wi: invalid index\n");
}

double
rgb_get_wi(rigid_body rgb_h, size_t i)
{
    rigid_body_t* rgb = (rigid_body_t*)rgb_h;
    if (i < 3)
        return rgb->w[i];
    else {
        fprintf(stderr, "rgb_get_wi: invalid index\n");
        return NAN;
    }
}