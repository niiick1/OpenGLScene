#include "Data/Vector.h"
#include <cmath>

Vector3 Vector3::normalize()
{
    float length = sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));

    return Vector3(this->x / length, this->y / length, this->z / length);
}

Vector3 Vector3::crossProduct(Vector3 v)
{
    return Vector3((this->y * v.z - (this->z * v.y)), (this->z * v.x - (this->x * v.z)), (this->x * v.y - (this->y * v.x)));
}

float Vector3::dotProduct(Vector3 v)
{
    return this->x*v.x + this->y*v.y + this->z*v.z;
}
