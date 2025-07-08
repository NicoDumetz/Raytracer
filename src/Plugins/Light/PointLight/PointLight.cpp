/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** PointLight
*/

#include "PointLight.hpp"

namespace Light {

PointLight::PointLight(const math::Point3D& position, const Utils::Color& intensity)
    : _position(position), _intensity(intensity)
{}

PointLight::PointLight(const Utils::ConfigNode& node)
    : _position(node.parsePoint3D("position")),
      _intensity(node.parseColor("color"))
{}

Utils::Color PointLight::illuminate(
    const Utils::HitRecord& hit,
    const RayTracer::Scene& scene
) const {
    math::Point3D P = hit.getPosition();
    math::Vector3D N = hit.getNormal().normalized();
    math::Vector3D L = (_position - P).normalized();
    double distance = (_position - P).length();
    const double eps = 1e-4;
    Utils::Ray shadowRay(P + L * eps, L);
    Utils::HitRecord tmp;
    if (scene.trace(shadowRay, tmp) && tmp.getDistance() < distance)
        return Utils::Color(0, 0, 0, 1.0f);
    float dotNL = std::max(0.0f, static_cast<float>(N.dot(L)));
    return Utils::Color(
        _intensity.r * dotNL,
        _intensity.g * dotNL,
        _intensity.b * dotNL,
        1.0f
    );
}

} // namespace Light


extern "C" {

void registerPlugin(RayTracer::Factory<Light::ILight>& factory)
{
    factory.addCreator("point", [](const Utils::ConfigNode& node) {
        return std::make_unique<Light::PointLight>(node);
    });
}

RayTracer::Ltype type()
{
    return RayTracer::Ltype::LIGHT;
}

const char* name()
{
    return "point";
}

}
