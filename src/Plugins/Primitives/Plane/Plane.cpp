/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Plane.hpp"

namespace Primitive {

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
    /* std::cout << "Passe dans hit" << std::endl;
    std::cout << "Transform" << std::endl << _transform << std::endl;
    std::cout << "Inverse" << std::endl <<_inverseTransform << std::endl; */
    const double epsilon = 1e-6;

    Utils::Ray localRay = _inverseTransform.transform(ray);
    double denom = _normal.dot(localRay.getDirection());
    if (denom >= 0.0 || std::abs(denom) < epsilon)
        return false;

    double t = (_position - localRay.getOrigin()).dot(_normal) / denom;
    if (t < epsilon)
        return false;

    math::Point3D localHit = localRay.at(t);
    math::Point3D worldHit = _transform.transform(localHit);
    math::Vector3D worldNormal = _transform.rotateVector(_normal).normalized();

    record.setDistance((worldHit - ray.getOrigin()).length());
    record.setPosition(worldHit);
    record.setNormal(worldNormal);
    record.setMaterial(_material);
    return true;
}

} // namespace Primitive


extern "C" {

    void registerPlugin(RayTracer::Factory<Primitive::IPrimitive>& factory)
    {
        factory.addCreator("plane", [](const Utils::ConfigNode& node) {
            return std::make_unique<Primitive::Plane>(node);
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