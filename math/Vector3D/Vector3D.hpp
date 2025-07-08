/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once

#include <cmath>
#include "../Point3D/Point3D.hpp"

namespace math
{

class Vector3D
{
public:
    double x;
    double y;
    double z;

    Vector3D(double x = 0, double y = 0, double z = 0);
    ~Vector3D() = default;
    double length() const;
    double dot(Vector3D &other) const;

    Vector3D &operator+(const Vector3D &other) const;
    void operator+=(const Vector3D &other);
    Vector3D &operator-(const Vector3D &other) const;
    void operator-=(const Vector3D &other);

    Vector3D &operator*(double value) const;
    void operator*=(double value);
    Vector3D &operator/(double value) const;
    void operator/=(double value);
};
} // namespace math
