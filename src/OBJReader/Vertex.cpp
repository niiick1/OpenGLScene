#include "OBJReader/Vertex.h"

Vertex::Vertex(float x, float y, float z) :
    _x(x),
    _y(y),
    _z(z)
{}

Vertex::~Vertex() {}

Vertex& Vertex::translateX(float distance) {
    _x += distance;

    return *this;
}
