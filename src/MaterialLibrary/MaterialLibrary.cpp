#include "MaterialLibrary/MaterialLibrary.h"

#include <iostream>
#include <GL/glew.h>
#include "lodepng/lodepng.h"

MaterialLibrary::MaterialLibrary()
{
    //ctor
}

MaterialLibrary::~MaterialLibrary()
{
    //dtor
}

void MaterialLibrary::addMaterial(const Material& material)
{
    std::string materialName = material.getName();

    if (materials.find(materialName) == materials.end()) {
        materials.insert(std::map<std::string, Material>::value_type(materialName, material));
    } else {
        std::cerr << "Material with name " << materialName << " already exists.\n";
    }
}

void MaterialLibrary::addMaterial(const std::vector<Material>& materials)
{
    for (std::vector<Material>::const_iterator it = materials.begin(); it != materials.end(); ++it) {
        Material material = *it;

        addMaterial(material);
    }
}

Material MaterialLibrary::getMaterial(std::string name)
{
    std::map<std::string, Material>::iterator material = materials.find(name);
    if (material == materials.end()) {
        return Material("");
    } else {
        return material->second;
    }
}

unsigned MaterialLibrary::getMaterialTexture(std::string name)
{
    Material material = getMaterial(name);

    if (material.getName().empty()) return -1;

    std::string textureName = material.getDiffuseTexture();

    if (textureIDs.find(textureName) == textureIDs.end()) {
        textureIDs[textureName] = loadTexture(textureName);
    } else {
        return textureIDs[textureName];
    }

    return 0;
}

unsigned MaterialLibrary::loadTexture(std::string textureFilename)
{
    Image textureData = readPNG(textureFilename.c_str());

    unsigned texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureData.w, textureData.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &textureData.data[0]);

    return texId;
}

MaterialLibrary::Image MaterialLibrary::readPNG(const char* file)
{
    std::vector<unsigned char> img;
    unsigned w, h;

    lodepng::decode(img, w, h, file);

    Image image;
    image.data = img;
    image.w = w;
    image.h = h;

    return image;
}
