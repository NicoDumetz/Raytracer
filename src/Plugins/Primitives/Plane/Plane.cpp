/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Plane.hpp"

namespace Primitive
{

Plane::Plane(std::shared_ptr<Material::IMaterial> material,
             math::Point3D point,
             math::Vector3D normal)
    : APrimitive(std::move(material), point), _normal(normal.normalized()) {}

Plane::Plane(const Utils::ConfigNode& node)
    : APrimitive(node.getMaterial(), node.parsePoint3D("point"))
{
    _normal = node.parseVector3("normal").normalized();
}

bool Plane::hit(const Utils::Ray &ray, Utils::HitRecord &record) const
{
    const double epsilon = 1e-6;
    double denom = _normal.dot(ray.getDirection());
    if (std::abs(denom) < epsilon)
        return false;

    double t = (_position - ray.getOrigin()).dot(_normal) / denom;
    if (t < epsilon)
        return false;

    math::Point3D hitPos = ray.getOrigin() + ray.getDirection() * t;
    math::Vector3D normal = _normal;

    record.setDistance(t);
    record.setPosition(hitPos);
    record.setNormal(normal);
    record.setMaterial(_material);
    return true;
}

void Plane::applyTransform(const math::TransformMatrix &transform)
{
    _position = transform.transform(_position);
    _normal = transform.rotateVector(_normal).normalized();
}

} // namespace Primitive


