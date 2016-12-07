#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

class Material
{
    public:
        Material() : name("") {}
        Material(std::string name);
        virtual ~Material();

        const std::string& getName() const { return name; }
        const float* getAmbientColor() const { return ambientColor; }
        const float* getDiffuseColor() const { return diffuseColor; }
        const float* getSpecularColor() const { return specularColor; }
        float getSpecularExponent() const { return specularExponent; }
        const std::string& getDiffuseTexture() const { return diffuseTexture; }

        Material& setAmbientColor(float r, float g, float b);
        Material& setDiffuseColor(float r, float g, float b);
        Material& setSpecularColor(float r, float g, float b);
        Material& setSpecularExponent(float e);
        Material& setDiffuseTexture(std::string filename);
    protected:
    private:
        std::string name;

        float ambientColor[3],
            diffuseColor[3],
            specularColor[3],
            specularExponent;

        std::string diffuseTexture;
};

#endif // MATERIAL_H
