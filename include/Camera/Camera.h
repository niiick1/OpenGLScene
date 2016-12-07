#ifndef CAMERA_H
#define CAMERA_H

#include "Data/Vector.h"
#include "Data/Matrix.h"

const bool EULER_ANGLES = false;

class Camera
{
    public:
        Vector3 eye;
        Vector3 target;
        Vector3 up;

        Camera();
        Camera(Vector3 eye, Vector3 target, Vector3 up);
        virtual ~Camera();

        void rotate(float degX, float degY, float degZ);
        void translate(float x, float y, float z);
    protected:
    private:
        float totalRotationX, totalRotationY, totalRotationZ;

        Vector4 pitch(Vector4 direction, float deg);
        Vector4 yaw(Vector4 direction, float deg);
        Vector4 roll(Vector4 direction, float deg);

        Matrix4 rotate(Vector3 axis, float deg);
        Matrix4 rotateEuler(float xAngle, float yAngle, float zAngle);
};

#endif // CAMERA_H
