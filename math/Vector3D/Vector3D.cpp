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

double Vector3D::length() const {return std::sqrt(x * x + y * y + z * z);}

double Vector3D::dot(Vector3D &other) const {return x * other.x + y * other.y + z * other.z;};

/* arithmetic operators */

Vector3D &Vector3D::operator+(const Vector3D &vector) const
{
    Vector3D new_vector(x + vector.x, y + vector.y, z + vector.z);
    return new_vector;
}

void Vector3D::operator+=(const Vector3D &vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
}

Vector3D &Vector3D::operator-(const Vector3D &vector) const
{
    Vector3D new_vector(x - vector.x, y - vector.y, z - vector.z);
    return new_vector;
}

void Vector3D::operator-=(const Vector3D &vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
}

/***Vector with double operation***/

Vector3D &Vector3D::operator*(double value) const
{
    Vector3D new_vector(x * value, y * value, z *value);
    return new_vector;
}

void Vector3D::operator*=(double value)
{
    x *= value;
    y *= value;
    z *= value;
}

Vector3D &Vector3D::operator/(double value) const
{
    Vector3D new_vector(x / value, y / value, z / value);
    return new_vector;
}

void Vector3D::operator/=(double value)
{
    x /= value;
    y /= value;
    z /= value;
}
} // namespace math
