/*
** EPITECH PROJECT, 2025
** TransMatrix.hpp
** File description:
** Project
*/

#pragma once

#include "Tools/Math/Matrix/Matrix.hpp"
#include "Tools/Math/Point3D/Point3D.hpp"
#include "Tools/Math/Vector3D/Vector3D.hpp"
#include "Tools/Ray/Ray.hpp"
#include <cmath>

namespace math
{
    class TransformMatrix : public Matrix<4, 4> {
    public:
        TransformMatrix() : Matrix<4, 4>() {}
        TransformMatrix(const Matrix<4, 4>& base) : Matrix<4, 4>(base) {}
        void applyTranslation(const Vector3D& t);
        void applyScaling(const Vector3D& s);
        void applyRotationX(double angle);
        void applyRotationY(double angle);
        void applyRotationZ(double angle);
        void applyRotation(const Vector3D& axis, double angle);
        Point3D transform(const Point3D& p) const;
        Vector3D transform(const Vector3D& v) const;
        Utils::Ray transform(const Utils::Ray& ray) const;
        Vector3D rotateVector(const Vector3D& v) const;
        TransformMatrix inverse() const;
    };
} // namespace math