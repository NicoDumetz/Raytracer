/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** Torus
*/

#include "Torus.hpp"
#include <cmath>
#include <limits>
#include <complex>
#include <algorithm>

namespace Primitive {

Torus::Torus(std::shared_ptr<Material::IMaterial> material,
             math::Point3D center,
             double majorRadius,
             double minorRadius)
    : APrimitive(std::move(material), center),
      _majorRadius(majorRadius), _minorRadius(minorRadius), _box(calculateBox())
{}

Torus::Torus(const Utils::ConfigNode& node)
    : APrimitive(node.getMaterial(), node.parsePoint3D("center")), _box(calculateBox())
{
    _majorRadius = std::stof(node.get("major_radius"));
    _minorRadius = std::stof(node.get("minor_radius"));
    this->applyNodeTransform(node, _position);
}

bool Torus::hit(const Utils::Ray& ray, Utils::HitRecord& record) const
{
    Utils::Ray localRay = _inverseTransform.transform(ray);
    std::vector<double> roots = intersectTorusBody(localRay);
    double t = std::numeric_limits<double>::max();

    for (double root : roots) {
        if (root > 0.001 && root < t)
            t = root;
    }
    if (t == std::numeric_limits<double>::max())
        return false;
    math::Point3D localHit = localRay.at(t);
    math::Point3D worldHit = _transform.transform(localHit);
    double x = localHit.x;
    double y = localHit.y;
    double z = localHit.z;
    double sumSq = x * x + y * y + z * z;
    double R = _majorRadius;
    double r = _minorRadius;
    math::Vector3D localNormal = math::Vector3D(
        4 * x * (sumSq - R * R - r * r),
        4 * y * (sumSq - R * R - r * r + 2 * R * R),
        4 * z * (sumSq - R * R - r * r)
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

std::vector<double> Torus::intersectTorusBody(const Utils::Ray& localRay) const
{
    math::Point3D origin = localRay.getOrigin();
    math::Vector3D dir = localRay.getDirection();
    math::Vector3D oc = origin - _position;
    double R = _majorRadius;
    double r = _minorRadius;
    double ox = oc.x;
    double oy = oc.y;
    double oz = oc.z;;
    double dx = dir.x;
    double dy = dir.y;
    double dz = dir.z;
    double sum_d_sq = dx * dx + dy * dy + dz * dz;
    double e = ox * ox + oy * oy + oz * oz - R * R - r * r;
    double f = ox * dx + oy * dy + oz * dz;
    double four_R2 = 4.0 * R * R;
    double A = sum_d_sq * sum_d_sq;
    double B = 4.0 * sum_d_sq * f;
    double C = 2.0 * sum_d_sq * e + 4.0 * f * f + four_R2 * dy * dy;
    double D = 4.0 * f * e + 2.0 * four_R2 * oy * dy;
    double E = e * e - four_R2 * (r * r - oy * oy);
    return solveQuartic(A, B, C, D, E);
}

std::vector<double> Torus::solveQuartic(double A, double B, double C, double D, double E) const
{
    std::vector<double> roots;

    if (std::abs(A) < 1e-8)
        return roots;
    std::complex<double> coeffs[] = {E, D, C, B, A};
    std::complex<double> rts[4];
    const std::complex<double> i(0, 1);
    rts[0] = 1.0;
    rts[1] = -1.0;
    rts[2] = i;
    rts[3] = -i;
    for (int iter = 0; iter < 100; ++iter) {
        for (int j = 0; j < 4; ++j) {
            std::complex<double> prod = 1.0;
            for (int k = 0; k < 4; ++k) {
                if (j != k)
                    prod *= (rts[j] - rts[k]);
            }
            std::complex<double> f = coeffs[4];
            for (int k = 3; k >= 0; --k)
                f = f * rts[j] + coeffs[k];

            rts[j] -= f / prod;
        }
    }
    for (auto& root : rts) {
        if (std::abs(root.imag()) < 1e-6)
            roots.push_back(root.real());
    }
    std::sort(roots.begin(), roots.end());
    return roots;
}

} // namespace Primitive

extern "C" {

void registerPlugin(RayTracer::Factory<Primitive::IPrimitive>& factory)
{
    factory.addCreator("torus", [](const Utils::ConfigNode& node) {
        return std::make_unique<Primitive::Torus>(node);
    });
}

RayTracer::Ltype type()
{
    return RayTracer::Ltype::PRIMITIVE;
}

const char* name()
{
    return "torus";
}

}
