/*
** EPITECH PROJECT, 2025
** FlatColor.hpp
** File description:
** raytracer
*/

#include "FlatColor.hpp"

namespace Material
{
    const Utils::Color& Material::FlatColor::shade(
        const Utils::HitRecord &,
        const Utils::Ray &,
        IMaterial::MaterialProperties&) const
    {
        return _color;
    }
} // namespace Material


Material::FlatColor::FlatColor(const Utils::ConfigNode& node)
    : _color(node.parseColor("color"))
{
}

extern "C" {

    void registerPlugin(RayTracer::Factory<Material::IMaterial>& factory)
    {
        factory.addCreator("flat", [](const Utils::ConfigNode& node) {
            return std::make_unique<Material::FlatColor>(node);
        });
    }

    RayTracer::Ltype type()
    {
        return RayTracer::Ltype::MATERIAL;
    }

    const char* name()
    {
        return "flat";
    }

}