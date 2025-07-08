/*
** EPITECH PROJECT, 2025
** Mirror.cpp
** File description:
** raytracer
*/

#include "Mirror.hpp"

namespace Material {

    Mirror::Mirror(Utils::Color color)
        : _color(color) {}

    Mirror::Mirror(const Utils::ConfigNode& node)
        : _color(node.parseColor("color")) {}

    const Utils::Color& Mirror::shade(
        const Utils::HitRecord&,
        const Utils::Ray&,
        IMaterial::MaterialProperties& props) const
    {
        props.reflectivity = 1.0f;
        props.transparency = 0.0f;
        props.refractiveIndex = 1.0f;
        return _color;
    }

}

extern "C" {

    void registerPlugin(RayTracer::Factory<Material::IMaterial>& factory)
    {
        factory.addCreator("mirror", [](const Utils::ConfigNode& node) {
            return std::make_unique<Material::Mirror>(node);
        });
    }

    RayTracer::Ltype type()
    {
        return RayTracer::Ltype::MATERIAL;
    }

    const char* name()
    {
        return "mirror";
    }

}
