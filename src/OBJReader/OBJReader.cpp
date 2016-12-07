#include "OBJReader/OBJReader.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <map>

#include "OBJReader/Vertex.h"
#include "OBJReader/Group.h"
#include "OBJReader/Face.h"

using namespace std;

OBJReader::OBJReader()
{
    //ctor
}

OBJReader::~OBJReader()
{
    //dtor
}

void OBJReader::getMeshFromFile(std::vector<Material>* materials, std::vector<Mesh*>* objects, const std::string& file)
{
    ifstream fileStream(file.c_str());

    Mesh* mesh = new Mesh();

    if (fileStream.fail()) {
        cout << "Error opening file " << file << endl;
    }

    Group currentGroup("");
    string line;
    string type;
    int vertexCount = 0,
        normalCount = 0,
        texelCount = 0;

    std::map<std::string, Material> materialMap;

    while (std::getline(fileStream >> std::ws, line)) {
        stringstream ss(line);

        ss >> type;

        if (type == "#") {
            continue;
        }

        if (type == "v") {
            mesh->addVertex(parseVertex(ss));
            vertexCount++;
            continue;
        }

        if (type == "vn") {
            mesh->addNormal(parseVertex(ss));
            normalCount++;
            continue;
        }

        if (type == "vt") {
            mesh->addTexel(parseTexel(ss));
            texelCount++;
            continue;
        }

        if (type == "g") {
            string groupName;

            if (currentGroup.getFaceCount() > 0) {
                mesh->addGroup(currentGroup);
            }

            std::getline(ss >> std::ws, groupName);

            currentGroup = Group(groupName);
            continue;
        }

        if (type == "f") {
            string triple;

            std::vector<const Vertex*> vertices;
            std::vector<const Vertex*> normals;
            std::vector<const TextureMapping*> texels;

            while (ss >> triple) {
                OBJReader::FaceVertex faceVertex = parseTriple(triple);

                try {
                    vertices.push_back(mesh->getVertex(faceVertex.v - 1));

                    if (faceVertex.n > 0) {
                        normals.push_back(mesh->getNormal(faceVertex.n - 1));
                    }

                    if (faceVertex.t > 0) {
                        texels.push_back(mesh->getTexel(faceVertex.t - 1));
                    }
                } catch (const std::out_of_range& oor) {
                    cerr << "Invalid .obj file" << endl;
                }
            }

            Face face(vertices);

            if (normals.size() > 0) {
                face.addNormals(normals);
            }

            if (texels.size() > 0) {
                face.addTexels(texels);
            }

            currentGroup.addFace(face);

            continue;
        }

        if (type == "mtllib") {
            string materialFile;

            ss >> materialFile;

            string filePath = getFilePath(file);

            if (filePath != "") {
                materialFile = filePath + "/" + materialFile;
            }

            std::vector<Material> readMaterials = this->getMaterialsFromFile(materialFile);
            materials->insert(materials->end(), readMaterials.begin(), readMaterials.end());

            for (std::vector<Material>::iterator it = materials->begin(); it != materials->end(); ++it) {
                materialMap[(*it).getName()] = *it;
            }

            continue;
        }

        if (type == "usemtl") {
            string materialName;

            ss >> materialName;

            std::map<std::string, Material>::iterator material = materialMap.find(materialName);

            if (material != materialMap.end()) {
                currentGroup.setMaterial(material->second);
            }
        }
    }

    mesh->addGroup(currentGroup);

    cout << "Read " << vertexCount << " vertices" << endl;
    cout << "Read " << normalCount << " normals" << endl;
    cout << "Read " << texelCount << " texels" << endl;

    objects->push_back(mesh);
}

std::vector<Material> OBJReader::getMaterialsFromFile(const std::string& file)
{
    std::vector<Material> materials;

    ifstream fileStream(file.c_str());

    if (fileStream.fail()) {
        cout << "Error opening file " << file << endl;
        return materials;
    }

    string line;
    string type;
    Material currentMaterial("");

    while (std::getline(fileStream >> std::ws, line)) {
        stringstream ss(line);

        ss >> type;

        if (type == "newmtl") {
            string materialName;
            ss >> materialName;

            if (currentMaterial.getName() != "") {
                materials.push_back(currentMaterial);
            }

            currentMaterial = Material(materialName);

            continue;
        }

        if (type == "Ka") {
            OBJReader::RGBColor color   = parseColor(ss);
            currentMaterial.setAmbientColor(color.r, color.g, color.b);

            continue;
        }

        if (type == "Kd") {
            OBJReader::RGBColor color = parseColor(ss);
            currentMaterial.setDiffuseColor(color.r, color.g, color.b);

            continue;
        }

        if (type == "Ks") {
            OBJReader::RGBColor color = parseColor(ss);
            currentMaterial.setSpecularColor(color.r, color.g, color.b);

            continue;
        }

        if (type == "Ns") {
            float specularExponent = 0;
            ss >> specularExponent;
            currentMaterial.setSpecularExponent(specularExponent);

            continue;
        }

        if (type == "map_Kd") {
            string textureFile;
            ss >> textureFile;

            string filePath = getFilePath(file);

            if (filePath != "") {
                textureFile = filePath + "/" + textureFile;
            }

            currentMaterial.setDiffuseTexture(textureFile);

            continue;
        }
    }

    materials.push_back(currentMaterial);

    return materials;
}

OBJReader::RGBColor OBJReader::parseColor(std::iostream& ss)
{
    float r, g, b;

    ss >> r >> g >> b;

    return OBJReader::RGBColor(r, g, b);
}

Vertex OBJReader::parseVertex(std::iostream& ss)
{
    float x, y, z;

    ss >> x >> y >> z;

    return Vertex(x, y, z);
}

TextureMapping OBJReader::parseTexel(std::iostream& ss)
{
    float u, v;

    ss >> u >> v;

    return TextureMapping(u, v);
}

OBJReader::FaceVertex OBJReader::parseTriple(const std::string& str)
{
    OBJReader::FaceVertex faceVertex;

    size_t index = 0;

    string value = str,
        separators = "/ \r\t";

    try {
        faceVertex.v = stoi(value);
    } catch (const std::invalid_argument& ia) {
        faceVertex.v = 0;
    }

    index = value.find_first_of(separators);

    // Only v
    if (index == string::npos || value.at(index) != '/') {
        return faceVertex;
    }

    index += 1;
    value = value.substr(index, value.length());

    // Handle v//n
    if (value.at(0) == '/') {
        try {
            faceVertex.n = stoi(value);
        } catch (const std::invalid_argument& ia) {
            faceVertex.n = 0;
        }

        return faceVertex;
    }

    try {
        faceVertex.t = stoi(value);
    } catch (const std::invalid_argument& ia) {
        faceVertex.t = 0;
    }

    index = value.find_first_of(separators);

    // v/t
    if (index == string::npos || value.at(index) != '/') {
        return faceVertex;
    }

    // v/t/n
    index += 1;
    value = value.substr(index, value.length());

    try {
        faceVertex.n = stoi(value);
    } catch (const std::invalid_argument& ia) {
        faceVertex.n = 0;
    }

    return faceVertex;
}

std::string OBJReader::getFilePath(const std::string& file)
{
    size_t pathIndex = file.find_last_of("/\\");
    string relativePath = "";

    if (pathIndex != string::npos) {
        relativePath = file.substr(0, pathIndex);
    }

    return relativePath;
}
