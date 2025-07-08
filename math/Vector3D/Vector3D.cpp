/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Vector3D.hpp"

namespace math
{
Vector3D::Vector3D(double x = 0, double y = 0, double z = 0)
: x(x), y(y), z(z) {}

double Vector3D::length() const {return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));};

double Vector3D::dot(Vector3D &other) const {return x * other.x + y * other.y + z * other.z;};

/* arithmetic operators */

Vector3D &Vector3D::operator+(const Vector3D &vector) const
{
    Vector3D new_vector(x + vector.x, y + vector.y, z + vector.z);
    return new_vector;
}

Vector3D &Vector3D::operator+=(const Vector3D &vector)
{
    x + vector.x;
    y + vector.y;
    z + vector.z;
    return *this;
}

Vector3D &Vector3D::operator-(const Vector3D &vector) const
{
    Vector3D new_vector(x - vector.x, y - vector.y, z - vector.z);
    return new_vector;
}

Vector3D &Vector3D::operator-=(const Vector3D &vector)
{
    x - vector.x;
    y - vector.y;
    z - vector.z;
    return *this;
}

Vector3D &Vector3D::operator*(const Vector3D &vector) const
{
    Vector3D new_vector(x * vector.x, y * vector.y, z * vector.z);
    return new_vector;
}

Vector3D &Vector3D::operator*=(const Vector3D &vector)
{
    x * vector.x;
    y * vector.y;
    z * vector.z;
    return *this;
}

Vector3D &Vector3D::operator/(const Vector3D &vector) const
{
    Vector3D new_vector(x / vector.x, y / vector.y, z / vector.z);
    return new_vector;
}

Vector3D &Vector3D::operator/=(const Vector3D &vector)
{
    x / vector.x;
    y / vector.y;
    z / vector.z;
    return *this;
}
 
} // namespace math
