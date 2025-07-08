/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once

#include "../../math/Point3D/Point3D.hpp"
#include "../../math/Vector3D/Vector3D.hpp"
#include "../Ray/Ray.hpp"

namespace RayTracer
{
class Sphere
{
public:
    math::Point3D _center;
    double _radius;

    Sphere(math::Point3D center, double radius);
    ~Sphere() = default;
    bool hit(Ray &ray) const {return false;};
private:
};
} // namespace RayTracer
