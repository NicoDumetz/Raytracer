/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Point3D.cpp
*/

#pragma once

#include "Tools/Math/Vector3D/Vector3D.hpp"

namespace math
{
class Point3D
{
public:
    double x, y, z;

    Point3D() : x(0), y(0), z(0) {}
    Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
    ~Point3D() = default;

    Vector3D operator-(const Point3D &other) const;
    Point3D operator+(const Vector3D &vec) const;
    Point3D operator-(const Vector3D &vec) const;

    void operator+=(const Vector3D &vec);
    void operator-=(const Vector3D &vec);
};
}