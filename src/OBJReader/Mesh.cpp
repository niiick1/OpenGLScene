#include "OBJReader/Mesh.h"

Mesh::Mesh()
{
    //ctor
}

Mesh::~Mesh() {
    for (std::vector<Vertex*>::iterator it = allVertex.begin() ; it != allVertex.end(); ++it) {
        delete *it;
    }

    for (std::vector<Vertex*>::iterator it = allNormals.begin() ; it != allNormals.end(); ++it) {
        delete *it;
    }
}

Mesh& Mesh::addVertex(Vertex v)
{
    this->allVertex.push_back(new Vertex(v.x(), v.y(), v.z()));

    return *this;
}

Mesh& Mesh::addNormal(Vertex v)
{
    this->allNormals.push_back(new Vertex(v.x(), v.y(), v.z()));

    return *this;
}

Mesh& Mesh::addTexel(TextureMapping tm)
{
    this->allMappings.push_back(new TextureMapping(tm.u(), tm.v()));

    return *this;
}

Mesh& Mesh::addGroup(Group group) {
    this->groups.push_back(group);

    return *this;
}

const Vertex* Mesh::getVertex(unsigned idx) const
{
    return this->allVertex.at(idx);
}

const Vertex* Mesh::getNormal(unsigned idx) const
{
    return this->allNormals.at(idx);
}

const TextureMapping* Mesh::getTexel(unsigned idx) const
{
    return this->allMappings.at(idx);
}
