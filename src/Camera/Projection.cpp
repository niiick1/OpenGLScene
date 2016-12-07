#include "Camera/Projection.h"

#include <iostream>
#include <cmath>

Projection::Projection()
    : projection(16, 0)
{
    projection[11] = -1;
    setPerspective(90.0, 1.33, 0.1, 100.0);
}

Projection::~Projection()
{
    //dtor
}

// Projection Matrix
//    Sx, 0, 0, 0,
//    0, Sy, 0, 0,
//    0, 0, Sz, -1,
//    0, 0, Pz, 0
void Projection::setPerspective(float fov, float aspect, float near, float far)
{
    float range = tan(fov * 0.5) * near,
        Sx = (2 * near) / (range * aspect + range * aspect),
        Sy = near / range,
        Sz = -(far + near) / (far - near),
        Pz = -(2 * far * near) / (far - near);

    projection[0] = Sx;
    projection[5] = Sy;
    projection[10] = Sz;
    projection[14] = Pz;
}
