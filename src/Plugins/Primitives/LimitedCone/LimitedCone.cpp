/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** LimitedCone
*/

#include "LimitedCone.hpp"
#include <cmath>
#include <limits>
#include <optional>

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
    std::optional<std::pair<double, math::Point3D>> bestHit;
    math::Vector3D bestNormal;

    if (disc >= 0) {
        double sqrtDisc = std::sqrt(disc);
        double t1 = (-b - sqrtDisc) / (2 * a);
        double t2 = (-b + sqrtDisc) / (2 * a);
        for (double t : {t1, t2}) {
            if (t > 0.001) {
                math::Point3D localHit = localRay.at(t);
                double yLocal = localHit.y - _position.y;
                if (yLocal >= _minY && yLocal <= _maxY) {
                    bestHit = std::make_pair(t, localHit);
                    bestNormal = math::Vector3D(
                        localHit.x,
                        k2 * yLocal,
                        localHit.z
                    ).normalized();
                }
            }
        }
    }
    for (auto [yOffset, normalDir] : std::array<std::pair<double, double>, 2>{
            {{_minY, -1.0}, {_maxY, 1.0}}}) {
        double yCap = _position.y + yOffset;
        if (std::abs(d.y) > 1e-6) {
            double t = (yCap - o.y) / d.y;
            if (t > 0.001) {
                math::Point3D p = localRay.at(t);
                double dx = p.x - _position.x;
                double dz = p.z - _position.z;
                double r = (yOffset / _height) * _radius;
                if (dx * dx + dz * dz <= r * r) {
                    if (!bestHit || t < bestHit->first) {
                        bestHit = std::make_pair(t, p);
                        bestNormal = math::Vector3D(0, normalDir, 0);
                    }
                }
            }
        }
    }
    if (!bestHit)
        return false;
    math::Point3D worldHit = _transform.transform(bestHit->second);
    math::Vector3D worldNormal = _transform.rotateVector(bestNormal).normalized();
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

