/*
** EPITECH PROJECT, 2025
** TransMatrixhpp
** File description:
** Project
*/

#include "TransformMatrix.hpp"

void math::Matrix4x4::applyTranslation(const Vector3D &t)
{
    Matrix4x4 m = Matrix();
    m(0, 3) = t.x;
    m(1, 3) = t.y;
    m(2, 3) = t.z;
    *this = (*this) * m;
}

void math::Matrix4x4::applyScaling(const Vector3D &s)
{
    Matrix4x4 m;
    m(0, 0) = s.x;
    m(1, 1) = s.y;
    m(2, 2) = s.z;
    *this = (*this) * m;
}

void math::Matrix4x4::applyRotationX(double angle)
{
    Matrix4x4 m = Matrix();
    double c = std::cos(angle);
    double s = std::sin(angle);
    m(1, 1) = c;
    m(1, 2) = -s;
    m(2, 1) = s;
    m(2, 2) = c;
    *this = (*this) * m;
}

void math::Matrix4x4::applyRotationY(double angle)
{
    Matrix4x4 m = Matrix();
    double c = std::cos(angle);
    double s = std::sin(angle);
    m(0, 0) = c;
    m(0, 2) = s;
    m(2, 0) = -s;
    m(2, 2) = c;
    *this = (*this) * m;
}

void math::Matrix4x4::applyRotationZ(double angle)
{
    Matrix4x4 m = Matrix();
    double c = std::cos(angle);
    double s = std::sin(angle);
    m(0, 0) = c;
    m(0, 1) = -s;
    m(1, 0) = s;
    m(1, 1) = c;
    *this = (*this) * m;
}

void math::Matrix4x4::applyRotation(const Vector3D &axis, double angle)
{
    Vector3D a = axis.normalized();
    double x = a.x, y = a.y, z = a.z;
    double c = std::cos(angle);
    double s = std::sin(angle);
    double t = 1 - c;

    Matrix4x4 m;
    m(0, 0) = t * x * x + c;
    m(0, 1) = t * x * y - s * z;
    m(0, 2) = t * x * z + s * y;
    m(0, 3) = 0;

    m(1, 0) = t * x * y + s * z;
    m(1, 1) = t * y * y + c;
    m(1, 2) = t * y * z - s * x;
    m(1, 3) = 0;

    m(2, 0) = t * x * z - s * y;
    m(2, 1) = t * y * z + s * x;
    m(2, 2) = t * z * z + c;
    m(2, 3) = 0;

    m(3, 0) = 0;
    m(3, 1) = 0;
    m(3, 2) = 0;
    m(3, 3) = 1;

    *this = (*this) * m;
}

math::Point3D math::Matrix4x4::transform(const Point3D &p) const
{
    Matrix<4, 1> vec({{{p.x}, {p.y}, {p.z}, {1.0}}});
    Matrix<4, 1> result = (*this) * vec;
    return Point3D(result(0, 0), result(1, 0), result(2, 0));
}

math::Vector3D math::Matrix4x4::transform(const Vector3D &v) const
{
    Matrix<4, 1> vec({{{v.x}, {v.y}, {v.z}, {0.0}}});
    Matrix<4, 1> result = (*this) * vec;
    return Vector3D(result(0, 0), result(1, 0), result(2, 0));
}
