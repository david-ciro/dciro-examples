#include "rigid_body.h"
#include <math.h>
#include <stdio.h>
#include <time.h>

double
by_name_0(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_m);
}

double
by_name_1(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_Ixx);
}

double
by_name_2(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_Ixy);
}

double
by_name_3(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_Ixz);
}

double
by_name_4(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_Iyy);
}

double
by_name_5(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_Iyz);
}

double
by_name_6(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_Izz);
}

double
by_name_7(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_x);
}

double
by_name_8(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_y);
}

double
by_name_9(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_z);
}

double
by_name_10(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_vx);
}

double
by_name_11(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_vy);
}

double
by_name_12(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_vz);
}

double
by_name_13(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_wx);
}

double
by_name_14(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_wy);
}

double
by_name_15(rigid_body rgb)
{
    return rgb_get_param(rgb, rgb_wz);
}

double
by_get_0(rigid_body rgb)
{
    return rgb_get_m(rgb);
}

double
by_get_1(rigid_body rgb)
{
    return rgb_get_Iij(rgb, 0, 0);
}

double
by_get_2(rigid_body rgb)
{
    return rgb_get_Iij(rgb, 0, 1);
}

double
by_get_3(rigid_body rgb)
{
    return rgb_get_Iij(rgb, 0, 2);
}

double
by_get_4(rigid_body rgb)
{
    return rgb_get_Iij(rgb, 1, 1);
}

double
by_get_5(rigid_body rgb)
{
    return rgb_get_Iij(rgb, 1, 2);
}

double
by_get_6(rigid_body rgb)
{
    return rgb_get_Iij(rgb, 2, 2);
}

double
by_get_7(rigid_body rgb)
{
    return rgb_get_xi(rgb, 0);
}

double
by_get_8(rigid_body rgb)
{
    return rgb_get_xi(rgb, 1);
}

double
by_get_9(rigid_body rgb)
{
    return rgb_get_xi(rgb, 2);
}

double
by_get_10(rigid_body rgb)
{
    return rgb_get_vi(rgb, 0);
}

double
by_get_11(rigid_body rgb)
{
    return rgb_get_vi(rgb, 1);
}

double
by_get_12(rigid_body rgb)
{
    return rgb_get_vi(rgb, 2);
}

double
by_get_13(rigid_body rgb)
{
    return rgb_get_wi(rgb, 0);
}

double
by_get_14(rigid_body rgb)
{
    return rgb_get_wi(rgb, 1);
}

double
by_get_15(rigid_body rgb)
{
    return rgb_get_wi(rgb, 2);
}

int
main()
{
    srand(time(NULL)); // Initialization, should only be called once.

    // list of functions to get by name
    double (*by_name[16])(rigid_body rgb) = {
        by_name_0,  by_name_1,  by_name_2,  by_name_3,
        by_name_4,  by_name_5,  by_name_6,  by_name_7,
        by_name_8,  by_name_9,  by_name_10, by_name_11,
        by_name_12, by_name_13, by_name_14, by_name_15
    };

    // list of functions to get by getter
    double (*by_get[16])(rigid_body rgb) = {
        by_get_0,  by_get_1,  by_get_2,  by_get_3,
        by_get_4,  by_get_5,  by_get_6,  by_get_7,
        by_get_8,  by_get_9,  by_get_10, by_get_11,
        by_get_12, by_get_13, by_get_14, by_get_15
    };

    // create a rigid body
    rigid_body rgb = rgb_create();

    size_t n_access = 1e7;
    size_t r;
    double value;

    // random access by name many times
    clock_t start = clock();
    for (size_t i = 0; i < n_access; i++) {
        r = rand() % 16;
        value = by_name[r](rgb);
    }
    clock_t end = clock();
    double  cpu_time_name = ((double)(end - start)) / CLOCKS_PER_SEC;

    // random access by get many times
    start = clock();
    for (size_t i = 0; i < n_access; i++) {
        r = rand() % 16;
        value = by_get[r](rgb);
    }
    end = clock();
    double cpu_time_get = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("%zu accesses by name in %.6e s\n", n_access,
           cpu_time_name);
    printf("%zu accesses by get in %.6e s\n", n_access, cpu_time_get);

    printf("rel. difference: %.6e %%\n",
           100 * fabs(cpu_time_get - cpu_time_name) /
             (cpu_time_name + cpu_time_get));
}