#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex.h"
#include "Group.h"
#include "TextureMapping.h"

class Mesh
{
    public:
        Mesh();
        virtual ~Mesh();

        Mesh& addVertex(Vertex v);
        Mesh& addNormal(Vertex v);
        Mesh& addTexel(TextureMapping tm);
        Mesh& addGroup(Group group);

        const Vertex* getVertex(unsigned idx) const;
        const Vertex* getNormal(unsigned idx) const;
        const TextureMapping* getTexel(unsigned idx) const;
        const std::vector<Group>& getGroups() const { return groups; }
    protected:
    private:
        std::vector<Vertex*> allVertex;
        std::vector<Vertex*> allNormals;
        std::vector<TextureMapping*> allMappings;
        std::vector<Group> groups;
};

#endif // MESH_H
