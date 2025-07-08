/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once

#include <cmath>
#include <ostream>

namespace math
{
class Vector3D
{
public:
    double x, y, z;

    Vector3D(double x = 0, double y = 0, double z = 0);
    ~Vector3D() = default;

    double length() const;
    bool isZero() const;

    double dot(const Vector3D& other) const;
    Vector3D cross(const Vector3D& other) const;
    Vector3D normalized() const;
    Vector3D reflect(const Vector3D& normal) const;


    Vector3D operator+(const Vector3D& other) const;
    void operator+=(const Vector3D& other);
    Vector3D operator-(const Vector3D& other) const;
    void operator-=(const Vector3D& other);
    Vector3D operator-() const;
    Vector3D operator*(const Vector3D& other) const;
    void operator*=(const Vector3D& other);

    Vector3D operator*(double scalar) const;
    void operator*=(double scalar);
    Vector3D operator/(double scalar) const;
    void operator/=(double scalar);
};
inline std::ostream& operator<<(std::ostream& os, const Vector3D& vec)
{
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}
}
