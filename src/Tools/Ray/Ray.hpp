/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once

#include "Tools/Math/Vector3D/Vector3D.hpp"
#include "Tools/Math/Point3D/Point3D.hpp"

namespace Utils
{
class Ray
{
public:
    math::Point3D O;
    math::Vector3D D;
    Ray();
    Ray(math::Point3D O, math::Vector3D D);
    ~Ray() = default;
    math::Point3D getOrigin() const { return O; }
    math::Vector3D getDirection() const { return D; }
    math::Point3D at(double t) const {return O + D * t;}
};
} // namespace RayTracer
