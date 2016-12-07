#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <GL/glew.h>
#include <string>

class ShaderLoader
{
    public:
        ShaderLoader();
        virtual ~ShaderLoader();

        GLuint load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
    protected:
    private:
        std::string loadShaderSource(const std::string& filename);
};

#endif // SHADERLOADER_H
