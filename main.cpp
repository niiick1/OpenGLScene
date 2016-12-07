#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>

#include "OBJReader/OBJReader.h"
#include "OBJReader/Mesh.h"

#include "GLSLAdapter/GLSLMesh.h"
#include "ShaderLoader/ShaderLoader.h"
#include "Data/Vector.h"
#include "Data/ObjectPosition.h"
#include "Camera/Projection.h"
#include "Camera/View.h"
#include "MaterialLibrary/MaterialLibrary.h"

#define _USE_MATH_DEFINES

#include <cmath>

#include "Camera/Camera.h"

using namespace std;

Vector3 eye(0, 25, 35);
//Vector3 eye(0, 0, 6);
Vector3 target(0, 0, 0);
Vector3 up(0, 1, 0);

Camera c(eye, target, up);

ObjectPosition meshPos(0, 0.5, 0);

struct Light {
    float position[4] = {0};

    float ambient[3] = {0};
    float diffuse[3] = {0};
    float specular[3] = {0};

    void setPosition(float x, float y, float z, float w) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
        position[3] = w;
    }

    void setAmbient(float r, float g, float b) {
        ambient[0] = r;
        ambient[1] = g;
        ambient[2] = b;
    }

    void setDiffuse(float r, float g, float b) {
        diffuse[0] = r;
        diffuse[1] = g;
        diffuse[2] = b;
    }

    void setSpecular(float r, float g, float b) {
        specular[0] = r;
        specular[1] = g;
        specular[2] = b;
    }
};

bool initGLEW()
{
    glewExperimental = true; // Needed in core profile
    return glewInit() == GLEW_OK;
}

float moveSpeed = 0.25;
float cameraSpeed = 5;
float objRotateSpeed = 30;
float objMoveSpeed = 5;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_W) {
            c.translate(0, 0, moveSpeed);
        }

        if (key == GLFW_KEY_S) {
            c.translate(0, 0, -moveSpeed);
        }

        if (key == GLFW_KEY_A) {
            c.translate(-moveSpeed, 0, 0);
        }

        if (key == GLFW_KEY_D) {
            c.translate(moveSpeed, 0, 0);
        }

        if (key == GLFW_KEY_Q) {
            c.translate(0, moveSpeed, 0);
        }

        if (key == GLFW_KEY_Z) {
            c.translate(0, -moveSpeed, 0);
        }

        if (key == GLFW_KEY_UP) {
            c.rotate(-cameraSpeed, 0, 0);
        }

        if (key == GLFW_KEY_DOWN) {
            c.rotate(cameraSpeed, 0, 0);
        }

        if (key == GLFW_KEY_RIGHT) {
            c.rotate(0, -cameraSpeed, 0);
        }

        if (key == GLFW_KEY_LEFT) {
            c.rotate(0, cameraSpeed, 0);
        }

        if (key == GLFW_KEY_COMMA) {
            c.rotate(0, 0, cameraSpeed);
        }

        if (key == GLFW_KEY_PERIOD) {
            c.rotate(0, 0, -cameraSpeed);
        }

        if (key == GLFW_KEY_I) {
            meshPos.rotate(-objRotateSpeed, 0, 0);
        }

        if (key == GLFW_KEY_K) {
            meshPos.rotate(objRotateSpeed, 0, 0);
        }

        if (key == GLFW_KEY_J) {
            meshPos.rotate(0, objRotateSpeed, 0);
        }

        if (key == GLFW_KEY_L) {
            meshPos.rotate(0, -objRotateSpeed, 0);
        }

        if (key == GLFW_KEY_U) {
            meshPos.rotate(0, 0, -objRotateSpeed);
        }

        if (key == GLFW_KEY_O) {
            meshPos.rotate(0, 0, objRotateSpeed);
        }

        if (key == GLFW_KEY_T) {
            meshPos.translate(0, 0, -objMoveSpeed);
        }

        if (key == GLFW_KEY_G) {
            meshPos.translate(0, 0, objMoveSpeed);
        }

        if (key == GLFW_KEY_F) {
            meshPos.translate(-objMoveSpeed, 0, 0);
        }

        if (key == GLFW_KEY_H) {
            meshPos.translate(objMoveSpeed, 0, 0);
        }

        if (key == GLFW_KEY_R) {
            meshPos.translate(0, objMoveSpeed, 0);
        }

        if (key == GLFW_KEY_V) {
            meshPos.translate(0, -objMoveSpeed, 0);
        }
    }
}

int main()
{
    GLFWwindow* window;
    float wWidth = 800, wHeight = 600;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(wWidth, wHeight, "Test Builder", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!initGLEW()) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    std::vector<Material> materials;
    std::vector<Mesh*> objects;

//    std::vector<Material> materials0;
//    std::vector<Mesh*> objects0;

    OBJReader reader;
    reader.getMeshFromFile(&materials, &objects, "resources/models/ground.obj");
    reader.getMeshFromFile(&materials, &objects, "resources/models/mesa.obj");

    MaterialLibrary materialLibrary;
    materialLibrary.addMaterial(materials);
//    materialLibrary.addMaterial(materials0);

   std::vector<GLSLMesh> meshes;

//    GLSLMesh meshes[2];
//    GLSLMesh m = *(objects[0]);
//    GLSLMesh m0 = *(objects[1]);
    for (int x = 0; x < objects.size(); x++) {
        GLSLMesh mesh(*objects[x]);
//        meshes[x] = mesh;
        meshes.push_back(mesh);
    }

//    for (int x = 0; x < objects0.size(); x++) {
//        GLSLMesh mesh(*objects0[x]);
//        meshes[x] = mesh;
//        meshes.push_back(mesh);
//    }

//    GLSLMesh mesh = meshes[0];
//    GLSLMesh mesh = meshes[0];
//    GLSLMesh mesh(*objects[0]);
//    mesh.setPosition(meshPos);

    Projection projection;
    projection.setPerspective(45, wWidth / wHeight, 0.1, 100.0);

    View view;

    Light light;
//    light.setPosition(-2, 10, 15, 0);
    light.setPosition(0, 5, 10, 0);
    light.setAmbient(1, 1, 1);
    light.setDiffuse(1, 1, 1);
//    light.setAmbient(0, 0, 0);
//    light.setDiffuse(0, 0, 0);
    light.setSpecular(1, 1, 1);

    // Shader compilation
    ShaderLoader sl;
    GLuint programID = sl.load("resources/shaders/vertexShader.glsl", "resources/shaders/fragmentShader.glsl");

    int projMatrixLocation = glGetUniformLocation(programID, "proj");
    int viewMatrixLocation = glGetUniformLocation(programID, "view");
    int modelTMatrixLocation = glGetUniformLocation(programID, "modelT");
    int modelRMatrixLocation = glGetUniformLocation(programID, "modelR");
    int lightAmbient = glGetUniformLocation(programID, "light.ambient");
    int lightDiffuse = glGetUniformLocation(programID, "light.diffuse");
    int lightPosition = glGetUniformLocation(programID, "light.position");
    int lightSpecular = glGetUniformLocation(programID, "light.specular");
    int materialAmbient = glGetUniformLocation(programID, "material.ambientColor");
    int materialDiffuse = glGetUniformLocation(programID, "material.diffuseColor");
    int materialSpecular = glGetUniformLocation(programID, "material.specularColor");
    int materialSpecularExp = glGetUniformLocation(programID, "material.specularExponent");
    int eyeLocation = glGetUniformLocation(programID, "eyeWorld");

    glUseProgram(programID);


    glUniform3fv(lightPosition, 1, light.position);
    glUniform3fv(lightAmbient, 1, light.ambient);
    glUniform3fv(lightDiffuse, 1, light.diffuse);
    glUniform3fv(lightSpecular, 1, light.specular);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.75f, 0.75f, 0.75f, 0.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        meshes[1].setPosition(meshPos);

        view.lookAt(c);
//        view.badLookAt(c.eye, c.target, c.up);
        glUniform3f(eyeLocation, c.eye.x, c.eye.y, c.eye.z);

        glUniformMatrix4fv(projMatrixLocation, 1, GL_FALSE, &projection.getMatrix()[0]);
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &view.getMatrix()[0]);

        for (std::vector<GLSLMesh>::iterator it = meshes.begin(); it != meshes.end(); it++) {
            GLSLMesh mesh = *it;

            glUniformMatrix4fv(modelTMatrixLocation, 1, GL_FALSE, mesh.getPosition().getTranslationMatrix());
            glUniformMatrix4fv(modelRMatrixLocation, 1, GL_FALSE, mesh.getPosition().getRotationMatrix());

            GLSLGroup group = mesh.getGroups()[0];

        //        glActiveTexture(GL_TEXTURE0);
            Material material = materialLibrary.getMaterial(group.getMaterialName());

            glUniform3fv(materialAmbient, 1, material.getAmbientColor());
            glUniform3fv(materialDiffuse, 1, material.getDiffuseColor());
            glUniform3fv(materialSpecular, 1, material.getSpecularColor());
            glUniform1f(materialSpecularExp, material.getSpecularExponent());
            //        std::cout << ambient[0] << " " << ambient[1] << " " << ambient[2] << '\n';

            GLuint textureID = materialLibrary.getMaterialTexture(group.getMaterialName());

            glBindTexture(GL_TEXTURE_2D, textureID);

            glBindVertexArray(group.getID());

            glDrawArrays(GL_TRIANGLES, 0, group.getVertexCount());
        }

//        glUniform1i(texturePixelsLocation, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
