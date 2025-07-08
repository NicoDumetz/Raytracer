/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Cylinder.hpp"

namespace Primitive {

Cylinder::Cylinder(std::shared_ptr<Material::IMaterial> material,
                    math::Point3D base,
                    double radius)
    : APrimitive(std::move(material), base), _base(base), _radius(radius), _box(calculateBox())
{}

Cylinder::Cylinder(const Utils::ConfigNode& node)
    : APrimitive(node.getMaterial(), node.parsePoint3D("center")), _box(calculateBox())
{
    _base = _position;
    if (!node.has("radius"))
        throw std::runtime_error("[Cylinder] Missing 'radius' in config node.");

    _radius = std::stof(node.get("radius"));
    this->applyNodeTransform(node, _base);
}

bool Cylinder::hit(const Utils::Ray& ray, Utils::HitRecord& record) const
{
    Utils::Ray localRay = _inverseTransform.transform(ray);
    math::Vector3D d = localRay.getDirection();
    math::Vector3D o = localRay.getOrigin() - _base;

    double dx = d.x, dz = d.z;
    double ox = o.x, oz = o.z;

    double a = dx * dx + dz * dz;
    double b = 2 * (dx * ox + dz * oz);
    double c = ox * ox + oz * oz - _radius * _radius;

    double discriminant = b * b - 4 * a * c;
    if (discriminant >= 0) {
        double sqrt_d = std::sqrt(discriminant);
        double t1 = (-b - sqrt_d) / (2 * a);
        double t2 = (-b + sqrt_d) / (2 * a);
        double t = (t1 > 0.001) ? t1 : (t2 > 0.001 ? t2 : -1.0);
        if (t > 0)
            return cylinderHit(localRay, ray, record, t);
    }
    return false;
}

bool Cylinder::cylinderHit(Utils::Ray localRay, const Utils::Ray& ray, Utils::HitRecord& record, double t) const
{
    math::Point3D localHit = localRay.at(t);
    math::Vector3D localNormal = math::Vector3D(localHit.x - _base.x, 0, localHit.z - _base.z).normalized();
    math::Point3D worldHit = _transform.transform(localHit);
    math::Vector3D worldNormal = _transform.rotateVector(localNormal).normalized();

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
        factory.addCreator("cylinder", [](const Utils::ConfigNode& node) {
            return std::make_unique<Primitive::Cylinder>(node);
        });
    }

    RayTracer::Ltype type()
    {
        return RayTracer::Ltype::PRIMITIVE;
    }

    const char* name()
    {
        return "cylinder";
    }

}