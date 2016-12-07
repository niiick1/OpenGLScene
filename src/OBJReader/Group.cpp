#include "OBJReader/Group.h"

Group::Group(std::string name) :
    name(name),
    material("")
{
    //ctor
}

Group::~Group() {}

Group& Group::addFace(Face face)
{
    this->groupFaces.push_back(face);

    return *this;
}

Group& Group::setMaterial(Material mat)
{
    this->material = mat;

    return *this;
}
