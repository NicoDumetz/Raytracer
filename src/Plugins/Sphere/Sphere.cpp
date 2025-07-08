/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Sphere.hpp"

namespace RayTracer
{
Sphere::Sphere(math::Point3D center = math::Point3D(), double radius = 0)
: _center(center), _radius(radius) {}

} // namespace RayTracer
