#include "Camera/View.h"

#include <cmath>
#include <iostream>

View::View() :
    view(16, 0)
{
    view[3] = 0;
    view[7] = 0;
    view[11] = 0;
    view[15] = 1;
}

View::~View()
{
    //dtor
}

//  View Matrix
//  r.x, up.x, -f.x, 0,
//  r.y, up.y, -f.y, 0,
//  r.z, up.z, -f.z, 0,
//  -eye.x, -eye.y, -eye.z, 1
void View::lookAt(Vector3 eye, Vector3 target, Vector3 up)
{
    Vector3 zaxis = Vector3(eye.x - target.x, eye.y - target.y, eye.z - target.z).normalize();
    Vector3 xaxis = up.crossProduct(zaxis).normalize();
    Vector3 yaxis = zaxis.crossProduct(xaxis);

//    std::cout << "Eye: " << eye.x << ' ' << eye.y << ' ' << eye.z << '\n';
//    std::cout << "Right (x): " << xaxis.x << ' ' << xaxis.y << ' ' << xaxis.z << '\n';
//    std::cout << "Up (y): " << yaxis.x << ' ' << yaxis.y << ' ' << yaxis.z << '\n';
//    std::cout << "Forward (z): " << zaxis.x << ' ' << zaxis.y << ' ' << zaxis.z << '\n';

    view[0] = xaxis.x;
    view[1] = yaxis.x;
    view[2] = zaxis.x;
    view[3] = 0;

    view[4] = xaxis.y;
    view[5] = yaxis.y;
    view[6] = zaxis.y;
    view[7] = 0;

    view[8] = xaxis.z;
    view[9] = yaxis.z;
    view[10] = zaxis.z;
    view[11] = 0;

    view[12] = -xaxis.dotProduct(eye);
    view[13] = -yaxis.dotProduct(eye);
    view[14] = -zaxis.dotProduct(eye);
    view[15] = 1;

//    for (int x = 0; x < 4; x++) {
//        for (int y = 0; y < 4; y++) {
//            std::cout << view[x*4 + y] << ' ';
//        }
//        std::cout << '\n';
//    }
}

void View::lookAt(Camera c)
{
    lookAt(c.eye, c.target, c.up);
}

void View::badLookAt(Vector3 eye, Vector3 target, Vector3 up)
{
    Vector3 d(target.x - eye.x, target.y - eye.y, target.z - eye.z);

//    Vector3 f = normalize(d);
    Vector3 f = d.normalize();

//    Vector3 r = crossProduct(f, up);
    Vector3 r = f.crossProduct(up);

    std::cout << "Eye: " << eye.x << ' ' << eye.y << ' ' << eye.z << '\n';
    std::cout << "Right (x): " << r.x << ' ' << r.y << ' ' << r.z << '\n';
    std::cout << "Up (y): " << up.x << ' ' << up.y << ' ' << up.z << '\n';
    std::cout << "Forward (z): " << f.x << ' ' << f.y << ' ' << f.z << '\n';

    view[0] = r.x;
    view[1] = up.x;
    view[2] = -f.x;
    view[3] = 0;

    view[4] = r.y;
    view[5] = up.y;
    view[6] = -f.y;
    view[7] = 0;

    view[8] = r.z;
    view[9] = up.z;
    view[10] = -f.z;
    view[11] = 0;

    view[12] = -eye.z;
    view[13] = -eye.y;
    view[14] = -eye.x;
    view[15] = 1;

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            std::cout << view[x*4 + y] << ' ';
        }
        std::cout << '\n';
    }
}
