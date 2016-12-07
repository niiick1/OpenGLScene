#ifndef PROJECTION_H
#define PROJECTION_H

#include <vector>

class Projection
{
    public:
        Projection();
        virtual ~Projection();

        void setPerspective(float fov, float aspect, float near, float far);
        std::vector<float>& getMatrix() { return projection; }
    protected:
    private:
        std::vector<float> projection;
};

#endif // PROJECTION_H
