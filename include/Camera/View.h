#ifndef VIEW_H
#define VIEW_H

#include <vector>

#include "Data/Vector.h"
#include "Data/Matrix.h"
#include "Camera/Camera.h"

class View
{
    public:
        View();
        virtual ~View();

        void lookAt(Vector3 eye, Vector3 center, Vector3 up);
        void lookAt(Camera c);
        void badLookAt(Vector3 eye, Vector3 center, Vector3 up);
        std::vector<float>& getMatrix() { return view; }

//        Vector3 crossProduct(Vector3 v0, Vector3 v1);
//        Vector3 normalize(Vector3 v);
//        float dotProduct(Vector3 v0, Vector3 v1);
    protected:
    private:

        std::vector<float> view;
};

#endif // VIEW_H
