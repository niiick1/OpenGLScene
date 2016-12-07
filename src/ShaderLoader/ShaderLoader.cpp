#include "ShaderLoader/ShaderLoader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

ShaderLoader::ShaderLoader()
{
    //ctor
}

ShaderLoader::~ShaderLoader()
{
    //dtor
}

GLuint ShaderLoader::load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
    std::string vertexShaderSource = loadShaderSource(vertexShaderFile),
        fragmentShaderSource = loadShaderSource(fragmentShaderFile);

    const char *vertexShaderSourcePointer = vertexShaderSource.c_str(),
        *fragmentShaderSourcePointer = fragmentShaderSource.c_str();

    GLint result = GL_FALSE;
	int InfoLogLength;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShaderSourcePointer, NULL);
    glCompileShader(vs);

    glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> vertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vs, InfoLogLength, NULL, &vertexShaderErrorMessage[0]);
		std::cout << "Vertex Shader Compile: " << &vertexShaderErrorMessage[0] << std::endl;
	}

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShaderSourcePointer, NULL);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> fragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vs, InfoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		std::cout << "Fragment Shader Compile: " << &fragmentShaderErrorMessage[0] << std::endl;
	}

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vs);
    glAttachShader(programID, fs);
    glLinkProgram(programID);

    return programID;
}

std::string ShaderLoader::loadShaderSource(const std::string& filename)
{
    std::ifstream fileStream(filename.c_str());

    if (fileStream.fail()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return "";
    }

    std::string line;
    std::stringstream ss;

    while (std::getline(fileStream, line)) {
        ss << line << '\n';
    }

    fileStream.close();

    return ss.str();
}

