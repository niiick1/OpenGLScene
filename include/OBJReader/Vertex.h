#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <iomanip>

class Vertex
{
    public:
        Vertex(float x, float y, float z);
        virtual ~Vertex();

        float x() const { return _x; }
        float y() const { return _y; }
        float z() const { return _z; }

        Vertex& translateX(float distance);
    protected:
    private:
        float _x, _y, _z;
};

#endif // VERTEX_H
