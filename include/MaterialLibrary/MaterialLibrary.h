#ifndef MATERIALLIBRARY_H
#define MATERIALLIBRARY_H

#include <string>
#include <vector>
#include <map>
#include "OBJReader/Material.h"

class MaterialLibrary
{
    struct Image {
        std::vector<unsigned char> data;
        unsigned w, h;
    };

    public:
        MaterialLibrary();
        virtual ~MaterialLibrary();

        void addMaterial(const Material& material);
        void addMaterial(const std::vector<Material>& materials);
        Material getMaterial(std::string name);

        unsigned getMaterialTexture(std::string name);
    protected:
    private:
        unsigned loadTexture(std::string textureFilename);
        Image readPNG(const char* file);

        std::map<std::string, Material> materials;
        std::map<std::string, unsigned> textureIDs;
};

#endif // MATERIALLIBRARY_H
