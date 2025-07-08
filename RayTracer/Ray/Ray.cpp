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
: _origin(math::Point3D()), _direction(math::Vector3D()) {}

Ray::Ray(math::Point3D origin, math::Vector3D direction)
: _origin(origin), _direction(direction) {}

} // namespace RayTracer
