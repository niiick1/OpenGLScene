#define _USE_MATH_DEFINES

#include <cmath>

#include "Camera/Camera.h"
#include "Camera/View.h"
#include "Data/Matrix.h"

#include <iostream>

Camera::Camera() :
    up(Vector3(0, 1, 0)),
    totalRotationX(0), totalRotationY(0), totalRotationZ(0)
{

}

Camera::Camera(Vector3 eye, Vector3 target, Vector3 up) :
    eye(eye), target(target), up(up),
    totalRotationX(0), totalRotationY(0), totalRotationZ(0)
{

}

Camera::~Camera()
{
    //dtor
}

void Camera::translate(float x, float y, float z)
{
    eye = Vector3(eye.x + x, eye.y + y, eye.z + z);
    target = Vector3(target.x + x, target.y + y, target.z + z);
}

void Camera::rotate(float degX, float degY, float degZ)
{
    Vector4 direction(eye.x - target.x, eye.y - target.y, eye.z - target.z, 1.0);

    if (EULER_ANGLES) {
        Matrix4 m = rotateEuler(degX, degY, degZ);
        direction = m * direction;

        eye = direction.xyz();
        up = (m * Vector4(up, 1.f)).xyz();
    } else {
        if (degX != 0) {
            direction = pitch(direction, degX);

            totalRotationX = fmod(totalRotationX + degX, 360.f);
        }

        if (degY != 0) {
            direction = yaw(direction, degY);

            totalRotationY = fmod(totalRotationY + degY, 360.f);
        }

        eye = Vector3(direction.x + target.x, direction.y + target.y, direction.z + target.z);

        if (degZ != 0) {
            up = roll(direction, degZ).xyz();

            totalRotationZ = fmod(totalRotationZ + degZ, 360.f);
        }
    }
}

Vector4 Camera::pitch(Vector4 direction, float deg)
{
    View calc;

    Vector3 forward = direction.xyz().normalize();
    Vector3 right = forward.crossProduct(up);

    Matrix4 rotationPitch = rotate(right, deg);

    return rotationPitch * direction;
}

Vector4 Camera::yaw(Vector4 direction, float deg)
{
    Matrix4 rotationYaw = rotate(up, deg);

    return rotationYaw * direction;
}

Vector4 Camera::roll(Vector4 direction, float deg)
{
    Vector3 forward = direction.xyz().normalize();

    Matrix4 rotationRoll = rotate(forward, deg);

    return rotationRoll * Vector4(up, 1.0);
}

Matrix4 Camera::rotate(Vector3 axis, float deg)
{
    float rotation[16] = {0};
    float angle = deg * M_PI / 180,
        rcos = cos(angle),
        rsin = sin(angle),
        u = axis.x,
        v = axis.y,
        w = axis.z;

	rotation[0] =      rcos + u*u*(1-rcos);
	rotation[4] =  w * rsin + v*u*(1-rcos);
	rotation[8] = -v * rsin + w*u*(1-rcos);
	rotation[1] = -w * rsin + u*v*(1-rcos);
	rotation[5] =      rcos + v*v*(1-rcos);
	rotation[9] =  u * rsin + w*v*(1-rcos);
	rotation[2] =  v * rsin + u*w*(1-rcos);
	rotation[6] = -u * rsin + v*w*(1-rcos);
	rotation[10] =      rcos + w*w*(1-rcos);
	rotation[15] = 1;

	return Matrix4(rotation);
}

Matrix4 Camera::rotateEuler(float xAngle, float yAngle, float zAngle)
{
    xAngle = fmod(xAngle, 360.0);
    yAngle = fmod(yAngle, 360.0);
    zAngle = fmod(zAngle, 360.0);

    float rotation[16];

    float
        radX = xAngle * M_PI / 180,
        radY = yAngle * M_PI / 180,
        radZ = zAngle * M_PI / 180,

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

    return Matrix4(rotation);
}
