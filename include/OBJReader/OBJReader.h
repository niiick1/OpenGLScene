#ifndef OBJREADER_H
#define OBJREADER_H

#include <string>
#include <sstream>
#include <vector>
#include "Mesh.h"
#include "TextureMapping.h"
#include "Material.h"

class OBJReader
{
    struct FaceVertex {
        int v, t, n;
        FaceVertex() :
            v(-1), t(-1), n(-1) {}
        FaceVertex(int v, int t, int n) :
            v(v), t(t), n(n) {}
    };

    struct RGBColor {
        float r, g, b;
        RGBColor(float r, float g, float b) :
            r(r), g(g), b(b) {}
    };

    public:
        OBJReader();
        virtual ~OBJReader();

        void getMeshFromFile(std::vector<Material>* materials, std::vector<Mesh*>* objects, const std::string& file);
        std::vector<Material> getMaterialsFromFile(const std::string& file);
    protected:
    private:
        Vertex parseVertex(std::iostream& ss);
        TextureMapping parseTexel(std::iostream& ss);
        FaceVertex parseTriple(const std::string& str);
        RGBColor parseColor(std::iostream& ss);
        std::string getFilePath(const std::string& file);
};

#endif // OBJREADER_H
