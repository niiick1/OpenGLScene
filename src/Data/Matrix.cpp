#include "Data/Matrix.h"

Matrix4::Matrix4()
{
    //ctor
}

Matrix4::~Matrix4()
{
    //dtor
}

Matrix4::Matrix4(float* mat)
{
    for (int x = 0; x < 16; x++) {
        m[x] = mat[x];
    }
}

Vector4 Matrix4::operator*(const Vector4& v)
{
    const int SIZE = 4;

    float r[4] = {0};

    for (int x = 0; x < SIZE; x++) {
        r[x] = m[x]*v.x + m[x + SIZE]*v.y + m[x + SIZE*2]*v.z + m[x + SIZE*3]*v.w;
    }

    return Vector4(r[0], r[1], r[2], r[3]);
}

Matrix4 Matrix4::operator*(const Matrix4& m1)
{
    const int SIZE = 4;

    float r[SIZE * SIZE] = {0};

    for (int x = 0; x < SIZE; x++) {
        int column = x * SIZE;

        for (int y = 0; y < SIZE; y++) {
            r[column + y] = m[column]*m1[y] + m[column + 1]*m1[y + SIZE] + m[column + 2]*m1[y + SIZE*2] + m[column + 3]*m1[y + SIZE*3];
        }
    }

    return Matrix4(r);
}
