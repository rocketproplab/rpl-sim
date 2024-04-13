#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3 {
   private:
   public:
    double x;
    double y;
    double z;

    Vector3();
    Vector3(double x, double y, double z);

    // Operators
    Vector3 operator+(const Vector3 &rhs) const
    {
        return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
    }

    Vector3 operator-(const Vector3 &rhs) const
    {
        return Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
    }

    Vector3 operator*(double scalar) const
    {
        return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
    }
};

#endif /* VECTOR3_H */