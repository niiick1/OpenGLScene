#include "OBJReader/Material.h"

Material::Material(std::string name) :
    name(name)
{
    //ctor
}

Material::~Material()
{
    //dtor
}

Material& Material::setAmbientColor(float r, float g, float b)
{
    this->ambientColor[0] = r;
    this->ambientColor[1] = g;
    this->ambientColor[2] = b;

    return *this;
}

Material& Material::setDiffuseColor(float r, float g, float b)
{
    this->diffuseColor[0] = r;
    this->diffuseColor[1] = g;
    this->diffuseColor[2] = b;

    return *this;
}

Material& Material::setSpecularColor(float r, float g, float b)
{
    this->specularColor[0] = r;
    this->specularColor[1] = g;
    this->specularColor[2] = b;

    return *this;
}

Material& Material::setSpecularExponent(float e)
{
    this->specularExponent = e;

    return *this;
}

Material& Material::setDiffuseTexture(std::string filename)
{
    this->diffuseTexture = filename;

    return *this;
}
