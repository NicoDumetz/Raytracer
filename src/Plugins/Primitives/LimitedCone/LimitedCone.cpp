/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** LimitedCone
*/

#include "LimitedCone.hpp"
#include <cmath>
#include <limits>

namespace Primitive {

LimitedCone::LimitedCone(std::shared_ptr<Material::IMaterial> material,
                         math::Point3D center,
                         double radius,
                         double height,
                         double minY,
                         double maxY)
    : APrimitive(std::move(material), center),
      _radius(radius), _height(height), _minY(minY), _maxY(maxY)
{}

LimitedCone::LimitedCone(const Utils::ConfigNode& node)
    : APrimitive(node.getMaterial(), node.parsePoint3D("center"))
{
    _radius = std::stof(node.get("radius"));
    _height = std::stof(node.get("height"));
    _minY = node.has("minY") ? std::stof(node.get("minY")) : -_height / 2;
    _maxY = node.has("maxY") ? std::stof(node.get("maxY")) : _height / 2;
    this->applyNodeTransform(node, _position);
}

bool LimitedCone::hit(const Utils::Ray& ray, Utils::HitRecord& record) const
{
    Utils::Ray localRay = _inverseTransform.transform(ray);
    math::Point3D o = localRay.getOrigin();
    math::Vector3D d = localRay.getDirection();
    double k = _radius / _height;
    double k2 = k * k;
    math::Vector3D oc = o - _position;
    double a = d.x * d.x + d.z * d.z - k2 * d.y * d.y;
    double b = 2 * (oc.x * d.x + oc.z * d.z - k2 * oc.y * d.y);
    double c = oc.x * oc.x + oc.z * oc.z - k2 * oc.y * oc.y;
    double disc = b * b - 4 * a * c;

    if (disc < 0)
        return false;
    double sqrtDisc = std::sqrt(disc);
    double t1 = (-b - sqrtDisc) / (2 * a);
    double t2 = (-b + sqrtDisc) / (2 * a);
    double t = -1.0;
    if (t1 > 0.001 && t2 > 0.001)
        t = std::min(t1, t2);
    else if (t1 > 0.001)
        t = t1;
    else if (t2 > 0.001)
        t = t2;
    if (t < 0)
        return false;
    math::Point3D localHit = localRay.at(t);
    double yLocal = localHit.y - _position.y;
    if (yLocal < _minY || yLocal > _maxY)
        return false;
    math::Point3D worldHit = _transform.transform(localHit);
    math::Vector3D localNormal = math::Vector3D(
        localHit.x,
        k2 * (localHit.y - _position.y),
        localHit.z
    ).normalized();
    math::Vector3D worldNormal = _transform.rotateVector(localNormal).normalized();
    if (worldNormal.dot(ray.getDirection()) > 0)
        worldNormal = -worldNormal;
    record.setDistance((worldHit - ray.getOrigin()).length());
    record.setPosition(worldHit);
    record.setNormal(worldNormal);
    record.setMaterial(_material);
    return true;
}

}


extern "C" {

void registerPlugin(RayTracer::Factory<Primitive::IPrimitive>& factory)
{
    factory.addCreator("limited_cone", [](const Utils::ConfigNode& node) {
        return std::make_unique<Primitive::LimitedCone>(node);
    });
}

RayTracer::Ltype type()
{
    return RayTracer::Ltype::PRIMITIVE;
}

const char* name()
{
    return "limited_cone";
}

}

