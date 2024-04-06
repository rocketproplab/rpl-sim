#include "Vector3.hpp"

// Standard Constructor initializes to given arguments.
Vector3::Vector3(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// Standard constructor initializes to 0
Vector3::Vector3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}