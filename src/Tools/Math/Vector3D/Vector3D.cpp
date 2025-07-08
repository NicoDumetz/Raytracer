/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Vector3D.hpp"

namespace math
{

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

double Vector3D::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

bool Vector3D::isZero() const {
    return x == 0 && y == 0 && z == 0;
}

double Vector3D::dot(const Vector3D& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::cross(const Vector3D& v) const {
    return Vector3D(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

Vector3D Vector3D::reflect(const Vector3D& normal) const
{
    return *this - normal * (2.0 * this->dot(normal));
}

Vector3D Vector3D::normalized() const {
    double len = length();
    return len != 0 ? *this / len : Vector3D(0, 0, 0);
}

// Operators

Vector3D Vector3D::operator+(const Vector3D& v) const {
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

void Vector3D::operator+=(const Vector3D& v) {
    x += v.x; y += v.y; z += v.z;
}

Vector3D Vector3D::operator-(const Vector3D& v) const {
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

void Vector3D::operator-=(const Vector3D& v) {
    x -= v.x; y -= v.y; z -= v.z;
}

Vector3D Vector3D::operator-() const {
    return Vector3D(-x, -y, -z);
}

Vector3D Vector3D::operator*(const Vector3D &other) const {
    return Vector3D(
        x * other.x,
        y * other.y,
        z * other.z
    );
}

void Vector3D::operator*=(const Vector3D& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
}

Vector3D Vector3D::operator*(double value) const {
    return Vector3D(x * value, y * value, z * value);
}

void Vector3D::operator*=(double value) {
    x *= value; y *= value; z *= value;
}

Vector3D Vector3D::operator/(double value) const {
    return Vector3D(x / value, y / value, z / value);
}

void Vector3D::operator/=(double value) {
    x /= value; y /= value; z /= value;
}
}

