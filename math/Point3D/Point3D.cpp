/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Point3D.cpp
*/

#include "Point3D.hpp"

/***Points operation***/

namespace math
{

Point3D &Point3D::operator+(const Point3D &point) const
{
    Point3D new_point(x + point.x, y + point.y, z + point.z);
    return new_point;
}

Point3D &Point3D::operator+=(const Point3D &point)
{
    x + point.x;
    y + point.y;
    z + point.z;
    return *this;
}

Point3D &Point3D::operator-(const Point3D &point) const
{
    Point3D new_point(x - point.x, y - point.y, z - point.z);
    return new_point;
}

Point3D &Point3D::operator-=(const Point3D &point)
{
    x - point.x;
    y - point.y;
    z - point.z;
    return *this;
}

Point3D &Point3D::operator*(const Point3D &point) const
{
    Point3D new_point(x * point.x, y * point.y, z * point.z);
    return new_point;
}

Point3D &Point3D::operator*=(const Point3D &point)
{
    x * point.x;
    y * point.y;
    z * point.z;
    return *this;
}

Point3D &Point3D::operator/(const Point3D &point) const
{
    Point3D new_point(x / point.x, y / point.y, z / point.z);
    return new_point;
}

Point3D &Point3D::operator/=(const Point3D &point)
{
    x / point.x;
    y / point.y;
    z / point.z;
    return *this;
}


/***Point with Vector operation***/

Point3D &Point3D::operator+(const Vector3D &vector) const
{
    Point3D new_point(x + vector.x, y + vector.y, z + vector.z);
    return new_point;
}

Point3D &Point3D::operator+=(const Vector3D &vector)
{
    x + vector.x;
    y + vector.y;
    z + vector.z;
    return *this;
}

Point3D &Point3D::operator-(const Vector3D &vector) const
{
    Point3D new_point(x - vector.x, y - vector.y, z - vector.z);
    return new_point;
}

Point3D &Point3D::operator-=(const Vector3D &vector)
{
    x - vector.x;
    y - vector.y;
    z - vector.z;
    return *this;
}

Point3D &Point3D::operator*(const Vector3D &vector) const
{
    Point3D new_point(x * vector.x, y * vector.y, z * vector.z);
    return new_point;
}

Point3D &Point3D::operator*=(const Vector3D &vector)
{
    x * vector.x;
    y * vector.y;
    z * vector.z;
    return *this;
}

Point3D &Point3D::operator/(const Vector3D &vector) const
{
    Point3D new_point(x / vector.x, y / vector.y, z / vector.z);
    return new_point;
}

Point3D &Point3D::operator/=(const Vector3D &vector)
{
    x / vector.x;
    y / vector.y;
    z / vector.z;
    return *this;
}
} // namespace math
