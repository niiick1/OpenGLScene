#ifndef GLSLGROUP_H
#define GLSLGROUP_H

#include <GL/glew.h>
#include <vector>
#include <string>

class GLSLGroup
{
    public:
        GLSLGroup(const std::vector<float>& vertices);
        virtual ~GLSLGroup();

        int getID() const { return vaoID; }

        int getVertexCount() const { return vertexCount; }

        std::string getMaterialName() { return materialName; }
        void setMaterialName(const std::string& name);

        void setTexels(const std::vector<float>& texels);
        void setNormals(const std::vector<float>& normals);
    protected:
    private:
        GLuint vaoID;
        GLuint vertexCount;
        std::string materialName;
};

#endif // GLSLGROUP_H
