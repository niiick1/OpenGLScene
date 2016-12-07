#ifndef OBJECTPOSITION_H
#define OBJECTPOSITION_H


class ObjectPosition
{
    public:
        ObjectPosition();
        ObjectPosition(float x, float y, float z);
        virtual ~ObjectPosition();

        void translate(float x, float y, float z);
        void rotate(float xAngle, float yAngle, float zAngle);

        float getX() const { return x; }
        void setX(float x);
        float getY() const { return y; }
        void setY(float y);
        float getZ() const { return z; }
        void setZ(float z);

        float* getTranslationMatrix() { return translation; }
        float* getRotationMatrix();
    protected:
    private:
        float degToRad(float deg);

        float x, y, z;
        float xAngle, yAngle, zAngle;
        float translation[16] = {0};
        float rotation[16] = {0};
};

#endif // OBJECTPOSITION_H
