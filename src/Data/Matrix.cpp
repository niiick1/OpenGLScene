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

//            r[0] = m1[0]*m2[0] + m1[1]*m2[4] + m1[2]*m2[8] + m1[3]*m2[12];
//            r[1] = m1[0]*m2[1] + m1[1]*m2[5] + m1[2]*m2[9] + m1[3]*m2[13];
//            r[2] = m1[0]*m2[2] + m1[1]*m2[6] + m1[2]*m2[10] + m1[3]*m2[14];
//            r[3] = m1[0]*m2[3] + m1[1]*m2[7] + m1[2]*m2[11] + m1[3]*m2[15];
//
//            r[4] = m1[4]*m2[0] + m1[5]*m2[4] + m1[6]*m2[8] + m1[7]*m2[12];
        }
    }

    return Matrix4(r);
}
