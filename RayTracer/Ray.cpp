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
: _origin(Point3D()), _direction(Vector3D()) {}

Ray::Ray(Point3D origin, Vector3D direction)
: _origin(origin), _direction(direction) {}

} // namespace RayTracer
