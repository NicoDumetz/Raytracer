/*
** EPITECH PROJECT, 2025
** Transparent.cpp
** File description:
** raytracer
*/

#include "Transparent.hpp"

namespace Material {

    Transparent::Transparent(Utils::Color color)
        : _color(color) {}

    Transparent::Transparent(const Utils::ConfigNode& node)
        : _color(node.parseColor("color")) {}

    const Utils::Color& Transparent::shade(
        const Utils::HitRecord&,
        const Utils::Ray&,
        IMaterial::MaterialProperties& props) const
    {
        props.reflectivity = 0.2f;
        props.transparency = 0.9f;
        props.refractiveIndex = 1.5f;
        return _color;
    }
}

extern "C" {

    void registerPlugin(RayTracer::Factory<Material::IMaterial>& factory)
    {
        factory.addCreator("transparent", [](const Utils::ConfigNode& node) {
            return std::make_unique<Material::Transparent>(node);
        });
    }

    RayTracer::Ltype type()
    {
        return RayTracer::Ltype::MATERIAL;
    }

    const char* name()
    {
        return "transparent";
    }

}
