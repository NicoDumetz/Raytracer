/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Ray.hpp"

namespace RayTracer
{
Ray::Ray()
: O(math::Point3D()), D(math::Vector3D()) {}

Ray::Ray(math::Point3D origin, math::Vector3D direction)
: O(origin), D(direction) {}

} // namespace RayTracer
