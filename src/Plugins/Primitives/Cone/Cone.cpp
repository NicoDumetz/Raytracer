/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Cone.hpp"

namespace Primitive {

Cone::Cone(std::shared_ptr<Material::IMaterial> material,
           math::Point3D apex,
           double height,
           double radius)
    : APrimitive(std::move(material), apex), _apex(apex), _height(height), _radius(radius)
{}

Cone::Cone(const Utils::ConfigNode& node)
    : APrimitive(node.getMaterial(), node.parsePoint3D("center"))
{
    _apex = _position;

    if (!node.has("radius") || !node.has("height"))
        throw std::runtime_error("[Cone] Missing 'radius' or 'height' in config node.");
    _radius = std::stof(node.get("radius"));
    _height = std::stof(node.get("height"));
    this->applyNodeTransform(node, _apex);
}

bool Cone::hit(const Utils::Ray& ray, Utils::HitRecord& record) const
{
    Utils::Ray localRay = _inverseTransform.transform(ray);
    math::Vector3D d = localRay.getDirection();
    math::Vector3D o = localRay.getOrigin() - _apex;

    double k = _radius / _height;
    double k2 = k * k;

    double dx = d.x, dy = d.y, dz = d.z;
    double ox = o.x, oy = o.y, oz = o.z;

    double a = dx * dx + dz * dz - k2 * dy * dy;
    double b = 2 * (dx * ox + dz * oz - k2 * dy * oy);
    double c = ox * ox + oz * oz - k2 * oy * oy;

    double discriminant = b * b - 4 * a * c;
    if (discriminant >= 0) {
        double sqrt_d = std::sqrt(discriminant);
        double t1 = (-b - sqrt_d) / (2 * a);
        double t2 = (-b + sqrt_d) / (2 * a);
        double t = (t1 > 0.001) ? t1 : (t2 > 0.001 ? t2 : -1.0);

        if (t > 0) {
            math::Point3D localHit = localRay.at(t);
            double y = localHit.y - _apex.y;
            if (y >= 0 && y <= _height) {
                math::Vector3D hitVec = localHit - _apex;
                double len = std::sqrt(hitVec.x * hitVec.x + hitVec.z * hitVec.z);
                if (len == 0)
                    return false;
                double cosAlpha = _height / std::sqrt(_height * _height + _radius * _radius);
                double sinAlpha = std::sqrt(1 - cosAlpha * cosAlpha);

                math::Vector3D projected = math::Vector3D(hitVec.x, 0, hitVec.z).normalized();
                math::Vector3D localNormal = (projected * cosAlpha - math::Vector3D(0, sinAlpha, 0)).normalized();

                math::Point3D worldHit = _transform.transform(localHit);
                math::Vector3D worldNormal = _transform.rotateVector(localNormal).normalized();

                record.setDistance((worldHit - ray.getOrigin()).length());
                record.setPosition(worldHit);
                record.setNormal(worldNormal);
                record.setMaterial(_material);
                return true;
            }
        }
    }

    return hitBottomCap(ray, record, localRay, d);
}

bool Cone::hitBottomCap(
    const Utils::Ray &ray,
    Utils::HitRecord &record,
    const Utils::Ray &localRay,
    const math::Vector3D &d) const
{
    math::Point3D baseCenter = _apex + math::Vector3D(0, _height, 0);
    math::Vector3D capNormal(0, 1, 0);
    double denom = capNormal.dot(d);
    if (std::abs(denom) > 1e-6) {
        double t_cap = (baseCenter - localRay.getOrigin()).dot(capNormal) / denom;
        if (t_cap > 0.001) {
            math::Point3D p_cap = localRay.at(t_cap);
            math::Vector3D dist = p_cap - baseCenter;
            if (dist.length() <= _radius) {
                math::Point3D worldHit = _transform.transform(p_cap);
                math::Vector3D worldNormal = _transform.rotateVector(capNormal).normalized();

                record.setDistance((worldHit - ray.getOrigin()).length());
                record.setPosition(worldHit);
                record.setNormal(worldNormal);
                record.setMaterial(_material);
                return true;
            }
        }
    }
    return false;
}

} // namespace Primitive

extern "C" {

    void registerPlugin(RayTracer::Factory<Primitive::IPrimitive>& factory)
    {
        factory.addCreator("cone", [](const Utils::ConfigNode& node) {
            return std::make_unique<Primitive::Cone>(node);
        });
    }

    RayTracer::Ltype type()
    {
        return RayTracer::Ltype::PRIMITIVE;
    }

    const char* name()
    {
        return "cone";
    }

}