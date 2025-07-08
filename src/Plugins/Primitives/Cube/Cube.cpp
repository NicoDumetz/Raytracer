/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** TanglesCubes
*/

#include "Cube.hpp"
#include <limits>

namespace Primitive {

Cube::Cube(std::shared_ptr<Material::IMaterial> material,
           math::Point3D center,
           double size)
    : APrimitive(std::move(material), center), _halfSize(size / 2.0)
{}

Cube::Cube(const Utils::ConfigNode& node)
    : APrimitive(node.getMaterial(), node.parsePoint3D("center"))
{
    if (!node.has("size"))
        throw std::runtime_error("[Cube] Missing 'size' field");
    _halfSize = std::stof(node.get("size")) / 2.0;
    this->applyNodeTransform(node, _position);
}
bool Cube::hit(const Utils::Ray& ray, Utils::HitRecord& record) const
{
    Utils::Ray localRay = _inverseTransform.transform(ray);
    math::Point3D origin = localRay.getOrigin();
    math::Vector3D dir = localRay.getDirection();
    math::Point3D min = _position - math::Vector3D(_halfSize, _halfSize, _halfSize);
    math::Point3D max = _position + math::Vector3D(_halfSize, _halfSize, _halfSize);
    double tmin = (min.x - origin.x) / dir.x;
    double tmax = (max.x - origin.x) / dir.x;

    if (tmin > tmax)
        std::swap(tmin, tmax);
    double tymin = (min.y - origin.y) / dir.y;
    double tymax = (max.y - origin.y) / dir.y;
    if (tymin > tymax)
        std::swap(tymin, tymax);
    if (tmin > tymax || tymin > tmax)
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;
    double tzmin = (min.z - origin.z) / dir.z;
    double tzmax = (max.z - origin.z) / dir.z;
    if (tzmin > tzmax)
        std::swap(tzmin, tzmax);
    if (tmin > tzmax || tzmin > tmax)
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;
    if (tmin < 0)
        tmin = tmax;
    if (tmin < 0)
        return false;
    math::Point3D localHit = localRay.at(tmin);
    math::Point3D worldHit = _transform.transform(localHit);
    math::Vector3D eps = localHit - _position;
    double bias = _halfSize - 1e-4;
    math::Vector3D localNormal;
    if (std::abs(eps.x) > bias)
        localNormal = math::Vector3D((eps.x > 0 ? 1 : -1), 0, 0);
    else if (std::abs(eps.y) > bias)
        localNormal = math::Vector3D(0, (eps.y > 0 ? 1 : -1), 0);
    else
        localNormal = math::Vector3D(0, 0, (eps.z > 0 ? 1 : -1));
    math::Vector3D worldNormal = _transform.rotateVector(localNormal).normalized();
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
    factory.addCreator("cube", [](const Utils::ConfigNode& node) {
        return std::make_unique<Primitive::Cube>(node);
    });
}

RayTracer::Ltype type()
{
    return RayTracer::Ltype::PRIMITIVE;
}

const char* name()
{
    return "cube";
}

}