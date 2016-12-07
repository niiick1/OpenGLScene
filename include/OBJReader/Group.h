#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <iostream>
#include <string>
#include "Face.h"
#include "Material.h"

class Group
{
    public:
        std::string name;

        Group(std::string name);
        virtual ~Group();

        Group& addFace(Face face);
        int getFaceCount() const { return groupFaces.size(); }
        const std::vector<Face> getFaces() const { return groupFaces; }

        Group& setMaterial(Material mat);
        Material getMaterial() const { return material; }
    protected:
    private:
        std::vector<Face> groupFaces;
        Material material;
};

#endif // GROUP_H
