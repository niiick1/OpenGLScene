#include "GLSLAdapter/GLSLMesh.h"
#include <GL/glew.h>

GLSLMesh::GLSLMesh(const Mesh& m)
{
    convert(m);
}

GLSLMesh::~GLSLMesh()
{
    //dtor
}

void GLSLMesh::convert(const Mesh& m)
{
    std::vector<Group> groups = m.getGroups();
    for (std::vector<Group>::iterator groupIterator = groups.begin(); groupIterator != groups.end(); groupIterator++) {
        Group group = *groupIterator;

        std::vector<float> vertices;
        std::vector<float> texels;
        std::vector<float> normals;

        std::vector<Face> faces = group.getFaces();
        for (std::vector<Face>::iterator faceIterator = faces.begin(); faceIterator != faces.end(); faceIterator++) {
            Face face = *faceIterator;

            std::vector<const Vertex*> faceVertices = face.getVertices();
            std::vector<const Vertex*> faceNormals = face.getNormals();
            std::vector<const TextureMapping*> faceTexels = face.getTexels();

            for (size_t x = 0; x < faceVertices.size(); x++) {
                const Vertex* v = faceVertices.at(x);

                vertices.push_back(v->x());
                vertices.push_back(v->y());
                vertices.push_back(v->z());

                if (x < faceTexels.size()) {
                    const TextureMapping* tm = faceTexels.at(x);

                    texels.push_back(tm->u());
                    texels.push_back(1 - tm->v());
                }

                if (x < faceNormals.size()) {
                    const Vertex* n = faceNormals.at(x);

                    normals.push_back(n->x());
                    normals.push_back(n->y());
                    normals.push_back(n->z());
                }
            }
        }

        // Bind to object
        GLSLGroup glslGroup(vertices);

        glslGroup.setTexels(texels);
        glslGroup.setNormals(normals);

        Material material = group.getMaterial();

//        if (material != nullptr) {
            glslGroup.setMaterialName(material.getName());
//        }

        this->groups.push_back(glslGroup);
    }
}
