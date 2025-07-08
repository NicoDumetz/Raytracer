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
    : APrimitive(node.getMaterial(), node.parsePoint3D("center"))
{
    if (!node.has("radius"))
        throw std::runtime_error("[Sphere] Missing 'radius' in config node.");
    _radius = std::stof(node.get("radius"));
}

bool Sphere::hit(const Utils::Ray &ray, Utils::HitRecord &record) const
{
    Utils::Ray localRay = _inverseTransform.transform(ray);

    math::Vector3D oc = localRay.getOrigin() - _position;

    double a = localRay.getDirection().dot(localRay.getDirection());
    double b = 2.0 * oc.dot(localRay.getDirection());
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    double sqrt_d = std::sqrt(discriminant);
    double t1 = (-b - sqrt_d) / (2 * a);
    double t2 = (-b + sqrt_d) / (2 * a);
    double t = (t1 > 0.001) ? t1 : (t2 > 0.001 ? t2 : -1.0);

    if (t < 0)
        return false;

    math::Point3D localHit = localRay.at(t);
    math::Point3D worldHit = _transform.transform(localHit);
    math::Vector3D localNormal = (localHit - _position).normalized();
    math::Vector3D worldNormal = _transform.rotateVector(localNormal).normalized();

    record.setDistance((worldHit - ray.getOrigin()).length());
    record.setPosition(worldHit);
    record.setNormal(worldNormal);
    record.setMaterial(_material);
    return true;
}
// void Sphere::applyTransform(const math::TransformMatrix &transform)
// {
//     _position = transform.transform(_position);
//     math::Vector3D scaled = transform.transform(math::Vector3D(_radius, 0, 0));
//     _radius = scaled.length();
// }
} // namespace RayTracer

extern "C" {

    void registerPlugin(RayTracer::Factory<Primitive::IPrimitive>& factory)
    {
        factory.addCreator("sphere", [](const Utils::ConfigNode& node) {
            return std::make_unique<Primitive::Sphere>(node);
        });
    }

    RayTracer::Ltype type()
    {
        return RayTracer::Ltype::PRIMITIVE;
    }

    const char* name()
    {
        return "plane";
    }

}