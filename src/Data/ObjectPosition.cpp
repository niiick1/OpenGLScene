#define _USE_MATH_DEFINES

#include "Data/ObjectPosition.h"
#include <cmath>

ObjectPosition::ObjectPosition() :
    x(0), y(0), z(0),
    xAngle(0), yAngle(0), zAngle(0)
{
    translation[0] = 1;
    translation[5] = 1;
    translation[10] = 1;
    translation[15] = 1;

    rotate(0, 0, 0);
}

ObjectPosition::ObjectPosition(float x, float y, float z) :
    x(x), y(y), z(z),
    xAngle(0), yAngle(0), zAngle(0)
{
    translation[0] = 1;
    translation[5] = 1;
    translation[10] = 1;
    translation[15] = 1;

    setX(x);
    setY(y);
    setZ(z);

    rotate(0, 0, 0);
}

ObjectPosition::~ObjectPosition()
{
    //dtor
}

void ObjectPosition::setX(float x)
{
    this->x = x;
    translation[12] = x;
}

void ObjectPosition::setY(float y)
{
    this->y = y;
    translation[13] = y;
}

void ObjectPosition::setZ(float z)
{
    this->z = z;
    translation[14] = z;
}

void ObjectPosition::translate(float x, float y, float z)
{
    translation[12] += x;
    translation[13] += y;
    translation[14] += z;

    this->x = translation[12];
    this->y = translation[13];
    this->z = translation[14];
}

void ObjectPosition::rotate(float xAngle, float yAngle, float zAngle)
{
    this->xAngle = fmod((this->xAngle + xAngle), 360.0);
    this->yAngle = fmod((this->yAngle + yAngle), 360.0);
    this->zAngle = fmod((this->zAngle + zAngle), 360.0);

    float
        radX = degToRad(this->xAngle),
        radY = degToRad(this->yAngle),
        radZ = degToRad(this->zAngle),

        A = cos(radX),
        B = sin(radX),
        C = cos(radY),
        D = sin(radY),
        E = cos(radZ),
        F = sin(radZ),

        AD = A * D,
        BD = B * D;

    rotation[0]  =   C * E;
    rotation[1]  =  -C * F;
    rotation[2]  =   D;
    rotation[4]  =  BD * E + A * F;
    rotation[5]  = -BD * F + A * E;
    rotation[6]  =  -B * C;
    rotation[8]  = -AD * E + B * F;
    rotation[9]  =  AD * F + B * E;
    rotation[10] =   A * C;

    rotation[3]  =  rotation[7] = rotation[11] = rotation[12] = rotation[13] = rotation[14] = 0;
    rotation[15] =  1;
}

float* ObjectPosition::getRotationMatrix()
{
    return rotation;
}

float ObjectPosition::degToRad(float deg)
{
    return deg * M_PI / 180.0f;
}
