/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** Triangles
*/

#include "Triangles.hpp"
#include <cmath>
#include <stdexcept>

namespace Primitive {

Triangle::Triangle(std::shared_ptr<Material::IMaterial> material,
                   math::Point3D a, math::Point3D b, math::Point3D c)
    : APrimitive(std::move(material), a), _a(a), _b(b), _c(c)
{
    _normal = ((_b - _a).cross(_c - _a)).normalized();
}

Triangle::Triangle(const Utils::ConfigNode& node)
    : APrimitive(node.getMaterial(), node.parsePoint3D("a"))
{
    if (!node.has("b") || !node.has("c"))
        throw std::runtime_error("[Triangle] Missing 'b' or 'c' in config");
    _a = node.parsePoint3D("a");
    _b = node.parsePoint3D("b");
    _c = node.parsePoint3D("c");
    _normal = ((_b - _a).cross(_c - _a)).normalized();
    this->applyNodeTransform(node, _position);
}

bool Triangle::hit(const Utils::Ray& ray, Utils::HitRecord& record) const
{
    Utils::Ray localRay = _inverseTransform.transform(ray);
    const math::Vector3D edge1 = _b - _a;
    const math::Vector3D edge2 = _c - _a;
    const math::Vector3D h = localRay.getDirection().cross(edge2);
    const double a = edge1.dot(h);
    if (std::abs(a) < 1e-6)
        return false; // Rayon parallèle au triangle
    const double f = 1.0 / a;
    const math::Vector3D s = localRay.getOrigin() - _a;
    const double u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
        return false;
    const math::Vector3D q = s.cross(edge1);
    const double v = f * localRay.getDirection().dot(q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    const double t = f * edge2.dot(q);
    if (t < 0.001)
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

}


extern "C" {
void registerPlugin(RayTracer::Factory<Primitive::IPrimitive>& factory)
{
    factory.addCreator("triangle", [](const Utils::ConfigNode& node) {
        return std::make_unique<Primitive::Triangle>(node);
    });
}

RayTracer::Ltype type()
{
    return RayTracer::Ltype::PRIMITIVE;
}

const char* name()
{
    return "triangle";
}
}
