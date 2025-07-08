/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** DirectionnalLight.cpp
*/

#include "AmbientLight.hpp"

Utils::Color Light::AmbientLight::illuminate(const Utils::HitRecord&, const RayTracer::Scene&) const {
    return _intensity;
}

Light::AmbientLight::AmbientLight(const Utils::ConfigNode& node)
    : _intensity(node.parseColor("color"))
{
}

extern "C" {

    void registerPlugin(RayTracer::Factory<Light::ILight>& factory)
    {
        factory.addCreator("ambient", [](const Utils::ConfigNode& node) {
            return std::make_unique<Light::AmbientLight>(node);
        });
    }

    RayTracer::Ltype type()
    {
        return RayTracer::Ltype::LIGHT;
    }

    const char* name()
    {
        return "ambient";
    }
}