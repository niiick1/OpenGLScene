#ifndef GLSLMESH_H
#define GLSLMESH_H

#include "OBJReader/Mesh.h"
#include "GLSLGroup.h"
#include "Data/ObjectPosition.h"
#include <vector>

class GLSLMesh
{
    public:
        GLSLMesh() {}
        GLSLMesh(const Mesh& m);
        virtual ~GLSLMesh();

        std::vector<GLSLGroup> getGroups() { return groups; }

        ObjectPosition getPosition() const { return position; }
        void setPosition(ObjectPosition pos) { position = pos; }

        void convert(const Mesh& m);
    protected:
    private:

        std::vector<GLSLGroup> groups;
        ObjectPosition position;
};

#endif // GLSLMESH_H
