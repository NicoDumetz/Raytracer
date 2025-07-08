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

void Point3D::operator+=(const Point3D &point)
{
    x += point.x;
    y += point.y;
    z += point.z;
}

Point3D &Point3D::operator-(const Point3D &point) const
{
    Point3D new_point(x - point.x, y - point.y, z - point.z);
    return new_point;
}

void Point3D::operator-=(const Point3D &point)
{
    x -= point.x;
    y -= point.y;
    z -= point.z;
}

/***Point with Vector operation***/

Point3D &Point3D::operator+(const Vector3D &vector) const
{
    Point3D new_point(x + vector.x, y + vector.y, z + vector.z);
    return new_point;
}

void Point3D::operator+=(const Vector3D &vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
}

Point3D &Point3D::operator-(const Vector3D &vector) const
{
    Point3D new_point(x - vector.x, y - vector.y, z - vector.z);
    return new_point;
}

void Point3D::operator-=(const Vector3D &vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
}

/***Point with double operation***/

Point3D &Point3D::operator+(const double &value) const
{
    Point3D new_point(x + value, y + value, z + value);
    return new_point;
}

void Point3D::operator+=(const double &value)
{
    x += value;
    y += value;
    z += value;
}

Point3D &Point3D::operator-(const double &value) const
{
    Point3D new_point(x - value, y - value, z - value);
    return new_point;
}

void Point3D::operator-=(const double &value)
{
    x -= value;
    y -= value;
    z -= value;
}

Point3D &Point3D::operator*(const double &value) const
{
    Point3D new_point(x * value, y * value, z * value);
    return new_point;
}

void Point3D::operator*=(const double &value)
{
    x *= value;
    y *= value;
    z *= value;
}

void Point3D::rotate(const Vector3D &axe, const double &angle)
{

}

Point3D &Point3D::operator/(const double &value) const
{
    Point3D new_point(x / value, y / value, z / value);
    return new_point;
}

void Point3D::operator/=(const double &value)
{
    x /= value;
    y /= value;
    z /= value;
}
}