#include "GLSLAdapter/GLSLGroup.h"

GLSLGroup::GLSLGroup(const std::vector<float>& vertices) :
    vertexCount(vertices.size())
{
    // Transform in VAO
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    glEnableVertexAttribArray(0);

    GLuint vertexVBO;
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

//    std::vector<float> colors = {
//        1.0, 0.0, 0.0,
//        0.0, 1.0, 0.0,
//        0.0, 0.0, 1.0,
//
//        1.0, 0.0, 0.0,
//        0.0, 1.0, 0.0,
//        0.0, 0.0, 1.0,
//
//        1.0, 0.0, 0.0,
//        0.0, 1.0, 0.0,
//        0.0, 0.0, 1.0,
//
//        1.0, 0.0, 0.0,
//        0.0, 1.0, 0.0,
//        0.0, 0.0, 1.0,
//
//        1.0, 0.0, 0.0,
//        0.0, 1.0, 0.0,
//        0.0, 0.0, 1.0,
//
//        1.0, 0.0, 0.0,
//        0.0, 1.0, 0.0,
//        0.0, 0.0, 1.0
//    };
//
//    glEnableVertexAttribArray(1);
//
//    GLuint colorVBO;
//    glGenBuffers(1, &colorVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * colors.size(), &colors[0], GL_STATIC_DRAW);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

GLSLGroup::~GLSLGroup()
{
    //dtor
}

void GLSLGroup::setMaterialName(const std::string& name)
{
    materialName = name;
}

void GLSLGroup::setTexels(const std::vector<float>& texels)
{
    if (texels.empty()) return;

    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(1);

    GLuint texelsVBO;
    glGenBuffers(1, &texelsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, texelsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texels.size(), &texels[0], GL_STATIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

void GLSLGroup::setNormals(const std::vector<float>& normals)
{
    if (normals.empty()) return;

    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(2);

    GLuint normalsVBO;
    glGenBuffers(1, &normalsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), &normals[0], GL_STATIC_DRAW);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}
