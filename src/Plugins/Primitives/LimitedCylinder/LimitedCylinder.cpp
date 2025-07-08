/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** LimitedCylinder
*/


#include "LimitedCylinder.hpp"
#include <cmath>
#include <limits>
#include "LimitedCylinder.hpp"
#include <cmath>
#include <limits>

namespace Primitive {

LimitedCylinder::LimitedCylinder(std::shared_ptr<Material::IMaterial> material,
                                 math::Point3D center,
                                 double radius,
                                 double height,
                                 double minY,
                                 double maxY)
    : APrimitive(std::move(material), center),
      _radius(radius), _height(height), _minY(minY), _maxY(maxY)
{}

LimitedCylinder::LimitedCylinder(const Utils::ConfigNode& node)
    : APrimitive(node.getMaterial(), node.parsePoint3D("center"))
{
    _radius = std::stof(node.get("radius"));
    _height = std::stof(node.get("height"));
    _minY = node.has("minY") ? std::stof(node.get("minY")) : -_height / 2;
    _maxY = node.has("maxY") ? std::stof(node.get("maxY")) : _height / 2;
    this->applyNodeTransform(node, _position);
}
bool LimitedCylinder::hit(const Utils::Ray& ray, Utils::HitRecord& record) const
{
    Utils::Ray localRay = _inverseTransform.transform(ray);
    math::Point3D o = localRay.getOrigin();
    math::Vector3D d = localRay.getDirection();
    math::Vector3D oc = o - _position;
    double a = d.x * d.x + d.z * d.z;
    double b = 2 * (oc.x * d.x + oc.z * d.z);
    double c = oc.x * oc.x + oc.z * oc.z - _radius * _radius;
    double disc = b * b - 4 * a * c;
    double tSide = std::numeric_limits<double>::infinity();

    if (disc >= 0) {
        double sqrtDisc = std::sqrt(disc);
        double t1 = (-b - sqrtDisc) / (2 * a);
        double t2 = (-b + sqrtDisc) / (2 * a);
        for (double t : {t1, t2}) {
            if (t > 0.001) {
                math::Point3D localHit = localRay.at(t);
                double yLocal = localHit.y - _position.y;
                if (yLocal >= _minY && yLocal <= _maxY) {
                    tSide = t;
                    break;
                }
            }
        }
    }
    double tCapBottom = std::numeric_limits<double>::infinity();
    if (std::abs(d.y) > 1e-6) {
        double t = (_minY + _position.y - o.y) / d.y;
        if (t > 0.001) {
            math::Point3D p = localRay.at(t);
            math::Vector3D v = p - _position;
            if ((v.x * v.x + v.z * v.z) <= _radius * _radius)
                tCapBottom = t;
        }
    }
    double tCapTop = std::numeric_limits<double>::infinity();
    if (std::abs(d.y) > 1e-6) {
        double t = (_maxY + _position.y - o.y) / d.y;
        if (t > 0.001) {
            math::Point3D p = localRay.at(t);
            math::Vector3D v = p - _position;
            if ((v.x * v.x + v.z * v.z) <= _radius * _radius)
                tCapTop = t;
        }
    }
    double t = std::min({tSide, tCapBottom, tCapTop});
    if (t == std::numeric_limits<double>::infinity())
        return false;
    math::Point3D localHit = localRay.at(t);
    math::Point3D worldHit = _transform.transform(localHit);
    math::Vector3D localNormal;
    if (t == tSide)
        localNormal = math::Vector3D(localHit.x - _position.x, 0, localHit.z - _position.z).normalized();
    else if (t == tCapBottom)
        localNormal = math::Vector3D(0, -1, 0);
    else
        localNormal = math::Vector3D(0, 1, 0);
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
    factory.addCreator("limited_cylinder", [](const Utils::ConfigNode& node) {
        return std::make_unique<Primitive::LimitedCylinder>(node);
    });
}

RayTracer::Ltype type()
{
    return RayTracer::Ltype::PRIMITIVE;
}

const char* name()
{
    return "limited_cylinder";
}

}
