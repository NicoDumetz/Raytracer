/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Point3D.cpp
*/

#include "Tools/Math/Point3D/Point3D.hpp"
#include "Point3D.hpp"

namespace math
{

double Point3D::dot(const Point3D &other) const
{
    return x * other.x + y * other.y + z * other.z;
}
double Point3D::dot(const math::Vector3D &other) const
{
    return x * other.x + y * other.y + z * other.z;
}
Vector3D Point3D::operator-(const Point3D &other) const
{
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Point3D Point3D::operator+(const Vector3D &vec) const
{
    return Point3D(x + vec.x, y + vec.y, z + vec.z);
}

Point3D Point3D::operator-(const Vector3D &vec) const
{
    return Point3D(x - vec.x, y - vec.y, z - vec.z);
}

void Point3D::operator+=(const Vector3D &vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
}

void Point3D::operator-=(const Vector3D &vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
}
}
