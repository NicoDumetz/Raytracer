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

bool Sphere::hit(Ray &ray) const
{
    double a = ray.D.dot(ray.D);
    double b = 2 * ray.O.dot(ray.D);
    double c = ray.O.dot(ray.O) - std::pow(R, 2);

    double d = std::pow(b, 2) - 4 * a * c;

    if (d < 0)
        return false;
    else
        return true;
}
} // namespace RayTracer
