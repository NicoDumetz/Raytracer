/*
** EPITECH PROJECT, 2025
** TransMatrixhpp
** File description:
** Project
*/

#include "TransformMatrix.hpp"
#include <iostream>

namespace math {

// === TRANSLATION ===

void TransformMatrix::applyTranslation(const Vector3D &t)
{
    TransformMatrix m;
    m(0, 3) = t.x;
    m(1, 3) = t.y;
    m(2, 3) = t.z;
    *this = m * (*this); // inversion ici
}

void TransformMatrix::applyTranslation(const Point3D &p)
{
    std::cout << "Point" << p.x << " "<< p.y << " "<< p.z << std::endl;
    std::cout << "Constructeur"<< std::endl;
    std::cout << "Avant" << *this << std::endl;
    applyTranslation(Vector3D(p.x, p.y, p.z));
    std::cout << "Après" << *this << std::endl;
}

// === SCALING ===

void TransformMatrix::applyScaling(const Vector3D &s)
{
    TransformMatrix m;
    m(0, 0) = s.x;
    m(1, 1) = s.y;
    m(2, 2) = s.z;
    *this = m * (*this); // inversion ici
}

// === ROTATIONS ===

void TransformMatrix::applyRotationX(double angle)
{
    TransformMatrix m;

    double c = std::cos(angle);
    double s = std::sin(angle);
    m(1, 1) = c;
    m(1, 2) = -s;
    m(2, 1) = s;
    m(2, 2) = c;
    *this = m * (*this);
}

void TransformMatrix::applyRotationY(double angle)
{
    TransformMatrix m;

    double c = std::cos(angle);
    double s = std::sin(angle);
    m(0, 0) = c;
    m(0, 2) = s;
    m(2, 0) = -s;
    m(2, 2) = c;
    *this = m * (*this);
}

void TransformMatrix::applyRotationZ(double angle)
{
    TransformMatrix m;

    double c = std::cos(angle);
    double s = std::sin(angle);
    m(0, 0) = c;
    m(0, 1) = -s;
    m(1, 0) = s;
    m(1, 1) = c;
    *this = m * (*this);
}

void TransformMatrix::applyRotation(const Vector3D &axis, double angle)
{
    Vector3D a = axis.normalized();
    double x = a.x, y = a.y, z = a.z;
    double c = std::cos(angle);
    double s = std::sin(angle);
    double t = 1.0 - c;

    TransformMatrix m;
    m(0, 0) = t * x * x + c;
    m(0, 1) = t * x * y - s * z;
    m(0, 2) = t * x * z + s * y;

    m(1, 0) = t * x * y + s * z;
    m(1, 1) = t * y * y + c;
    m(1, 2) = t * y * z - s * x;

    m(2, 0) = t * x * z - s * y;
    m(2, 1) = t * y * z + s * x;
    m(2, 2) = t * z * z + c;

    *this = m * (*this);
}

void TransformMatrix::rotateAroundPointX(const Point3D& pivot, double angle)
{
    applyTranslation(Vector3D(-pivot.x, -pivot.y, -pivot.z));
    applyRotationX(angle);
    applyTranslation(Vector3D(pivot.x, pivot.y, pivot.z));
}

void TransformMatrix::rotateAroundPointY(const Point3D& pivot, double angle)
{
    applyTranslation(Vector3D(-pivot.x, -pivot.y, -pivot.z));
    applyRotationY(angle);
    applyTranslation(Vector3D(pivot.x, pivot.y, pivot.z));
}

void TransformMatrix::rotateAroundPointZ(const Point3D& pivot, double angle)
{
    applyTranslation(Vector3D(-pivot.x, -pivot.y, -pivot.z));
    applyRotationZ(angle);
    applyTranslation(Vector3D(pivot.x, pivot.y, pivot.z));
}

void TransformMatrix::rotateAroundAxis(const Point3D& pivot, const Vector3D& axis, double angle)
{
    applyTranslation(Vector3D(-pivot.x, -pivot.y, -pivot.z));
    applyRotation(axis, angle);
    applyTranslation(Vector3D(pivot.x, pivot.y, pivot.z));
}



// === APPLICATION AUX OBJETS ===

Point3D TransformMatrix::transform(const Point3D &p) const
{
    Matrix<4, 1> vec({{{p.x}, {p.y}, {p.z}, {1.0}}});
    auto result = (*this) * vec;
    return Point3D(result(0, 0), result(1, 0), result(2, 0));
}

Vector3D TransformMatrix::transform(const Vector3D &v) const
{
    Matrix<4, 1> vec({{{v.x}, {v.y}, {v.z}, {0.0}}});
    auto result = (*this) * vec;
    return Vector3D(result(0, 0), result(1, 0), result(2, 0));
}

Utils::Ray TransformMatrix::transform(const Utils::Ray &ray) const
{
    return Utils::Ray(transform(ray.getOrigin()), rotateVector(ray.getDirection()));
}

Vector3D TransformMatrix::rotateVector(const Vector3D &v) const
{
    return {
        (*this)(0, 0) * v.x + (*this)(0, 1) * v.y + (*this)(0, 2) * v.z,
        (*this)(1, 0) * v.x + (*this)(1, 1) * v.y + (*this)(1, 2) * v.z,
        (*this)(2, 0) * v.x + (*this)(2, 1) * v.y + (*this)(2, 2) * v.z
    };
}

// === INVERSE (AFFINE) ===

TransformMatrix TransformMatrix::inverse() const
{
    Matrix<4, 4> inv;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            inv(i, j) = (*this)(j, i);
    for (int i = 0; i < 3; ++i) {
        inv(i, 3) = 0;
        for (int j = 0; j < 3; ++j)
            inv(i, 3) -= inv(i, j) * (*this)(j, 3);
    }
    inv(3, 0) = inv(3, 1) = inv(3, 2) = 0;
    inv(3, 3) = 1;

    return TransformMatrix(inv);
}

} // namespace math

