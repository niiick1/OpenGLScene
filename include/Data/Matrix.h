#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>

#include "Data/Vector.h"

class Matrix4
{
    public:
        Matrix4();
        Matrix4(float* mat);
        virtual ~Matrix4();

        float& operator[](std::size_t idx) { return m[idx]; }
        const float& operator[](std::size_t idx) const { return m[idx]; }

        Vector4 operator*(const Vector4& v);
        Matrix4 operator*(const Matrix4& m1);
//        Vector4 multiplyMat4xVec4(const Matrix4& m, Vector4);
    protected:
    private:
        float m[16] = {0};
};

#endif // MATRIX_H
