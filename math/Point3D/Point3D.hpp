/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Point3D.cpp
*/

#pragma once

#include "../Vector3D/Vector3D.hpp"

namespace math
{
class Point3D
{
public:
    double x;
    double y;
    double z;

    Point3D() : x(0), y(0), z(0){};
    Point3D(double x, double y, double z) : x(x), y(y), z(z) {};
    ~Point3D() = default;

    Point3D &operator+(const Point3D &point) const;
    void operator+=(const Point3D &point);
    Point3D &operator-(const Point3D &point) const;
    void operator-=(const Point3D &point);

    Point3D &operator+(const Vector3D &vector) const;
    void operator+=(const Vector3D &vector);
    Point3D &operator-(const Vector3D &vector) const;
    void operator-=(const Vector3D &vector);

    Point3D &operator+(const double &value) const;
    void operator+=(const double &value);
    Point3D &operator-(const double &value) const;
    void operator-=(const double &value);
    Point3D &operator/(const double &value) const;
    void operator/=(const double &value);
    Point3D &operator*(const double &value) const;
    void operator*=(const double &value);

    void rotate(const Vector3D &axe, const double &angle);
};
} // namespace math