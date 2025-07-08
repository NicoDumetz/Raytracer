/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Sphere.hpp"

namespace Primitive
{
Sphere::Sphere(std::shared_ptr<Material::IMaterial> material,
    math::Point3D center = math::Point3D(),
    double radius = 0)
: APrimitive(std::move(material), center), _radius(radius) {}

Sphere::Sphere(const Utils::ConfigNode& node)
    : APrimitive(node.getMaterial(), node.parsePoint3D("point"))
{
    if (!node.has("radius"))
        throw std::runtime_error("[Sphere] Missing 'radius' in config node.");
    _radius = std::stof(node.get("radius"));
}

bool Primitive::Sphere::hit(const Utils::Ray &ray, Utils::HitRecord &record) const
{
    math::Vector3D oc = ray.getOrigin() - _position;
    double a = ray.getDirection().dot(ray.getDirection());
    double b = 2.0 * oc.dot(ray.getDirection());
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    double sqrt_d = std::sqrt(discriminant);
    double t1 = (-b - sqrt_d) / (2 * a);
    double t2 = (-b + sqrt_d) / (2 * a);
    double t = -1;

    if (t1 > 0.001)
        t = t1;
    else if (t2 > 0.001)
        t = t2;

    if (t < 0)
        return false;

    math::Point3D hitPos = ray.getOrigin() + ray.getDirection() * t;
    math::Vector3D normal = (hitPos - _position).normalized();

    record.setDistance(t);
    record.setPosition(hitPos);
    record.setNormal(normal);
    record.setMaterial(_material);
    return true;
}
void Sphere::applyTransform(const math::TransformMatrix &transform)
{
    _position = transform.transform(_position);
    math::Vector3D scaled = transform.transform(math::Vector3D(_radius, 0, 0));
    _radius = scaled.length();
}
} // namespace RayTracer
