#ifndef FACE_H
#define FACE_H

#include <vector>
#include "Vertex.h"
#include "TextureMapping.h"

class Face
{
    public:
        Face(std::vector<const Vertex*> vertices);
        virtual ~Face();

        Face& addNormals(std::vector<const Vertex*> normals);
        Face& addTexels(std::vector<const TextureMapping*> texels);

        const std::vector<const Vertex*>& getVertices() const { return vertices; }
        const std::vector<const Vertex*>& getNormals() const { return normals; }
        const std::vector<const TextureMapping*>& getTexels() const { return mappings; }
    protected:
    private:
        std::vector<const Vertex*> vertices;
        std::vector<const Vertex*> normals;
        std::vector<const TextureMapping*> mappings;
};

#endif // FACE_H
