#include "OBJReader/Face.h"
#include <iostream>

Face::Face(std::vector<const Vertex*> vertices) :
    vertices(vertices)
{

}

Face::~Face()
{
    //dtor
}

Face& Face::addNormals(std::vector<const Vertex*> normals)
{
    this->normals = normals;

    return *this;
}

Face& Face::addTexels(std::vector<const TextureMapping*> texels)
{
    this->mappings = texels;

    return *this;
}
