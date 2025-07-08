/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** DirectionnalLight.cpp
*/

#include "DirectionnalLight.hpp"
#include <iostream>

Utils::Color Light::DirectionalLight::illuminate(
    const Utils::HitRecord& hit,
    const RayTracer::Scene& scene
) const {
    math::Point3D  P = hit.getPosition();
    math::Vector3D N = hit.getNormal().normalized();
    math::Vector3D L = -_direction.normalized();

    const double eps = 1e-4;
    Utils::Ray shadowRay(P + L * eps, L);
    Utils::HitRecord tmp;
    if (scene.trace(shadowRay, tmp)) {
        return Utils::Color(0,0,0,1.0f);
    }
    float dotNL = std::max(0.0f, static_cast<float>(N.dot(L)));

    return Utils::Color(
        _intensity.r * dotNL,
        _intensity.g * dotNL,
        _intensity.b * dotNL,
        1.0f
    );
}

Light::DirectionalLight::DirectionalLight(const Utils::ConfigNode& node)
    : _direction(node.parseVector3("direction").normalized()),
      _intensity(node.parseColor("color"))
{
}

extern "C" {

    void registerPlugin(RayTracer::Factory<Light::ILight>& factory)
    {
        factory.addCreator("directional", [](const Utils::ConfigNode& node) {
            return std::make_unique<Light::DirectionalLight>(node);
        });
    }

    RayTracer::Ltype type()
    {
        return RayTracer::Ltype::LIGHT;
    }

    const char* name()
    {
        return "directional";
    }
}