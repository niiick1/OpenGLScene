#ifndef VECTOR_H
#define VECTOR_H

class Vector3
{
    public:
        float x, y, z;

        Vector3() : x(0), y(0), z(0) {}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
        virtual ~Vector3() {}

        Vector3 normalize();
        Vector3 crossProduct(Vector3 v);
        float dotProduct(Vector3 v);
    protected:
    private:
};

class Vector4
{
    public:
        float x, y, z, w;

        Vector4() : x(0), y(0), z(0), w(0) {}
        Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
        Vector4(const Vector3& xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
        virtual ~Vector4() {}

        Vector3 xyz() const { return Vector3(x, y, z); }

    protected:
    private:
};

#endif // VECTOR_H
