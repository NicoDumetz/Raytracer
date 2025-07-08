/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once

#include "../math/Vector3D/Vector3D.hpp"
// #include "../math/Point3D/Point3D.hpp"

namespace RayTracer
{
class Ray
{
public:
    Point3D _origin;
    Vector3D _direction;
    Ray();
    Ray(Point3D origin, Vector3D direction);
    ~Ray() = default;
private:
};
} // namespace RayTracer
