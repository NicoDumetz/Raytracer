/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** Gradient
*/


#include "Gradient.hpp"
#include <algorithm>

namespace Material {

GradientColor::GradientColor(const Utils::ConfigNode& node)
    : _colorTop(node.parseColor("colorTop")),
      _colorBottom(node.parseColor("colorBottom"))
{}

const Utils::Color& GradientColor::shade(const Utils::HitRecord& rec,
                                         const Utils::Ray& ,
                                         MaterialProperties&) const
{
    float y = rec.getPosition().y;
    float alpha = (y + 1000.f) / 2000.f;
    alpha = std::clamp(alpha, 0.f, 1.f);
    _result.r = _colorBottom.r * (1 - alpha) + _colorTop.r * alpha;
    _result.g = _colorBottom.g * (1 - alpha) + _colorTop.g * alpha;
    _result.b = _colorBottom.b * (1 - alpha) + _colorTop.b * alpha;
    _result.a = 1.0f;
    return _result;
}

}

extern "C" {

void registerPlugin(RayTracer::Factory<Material::IMaterial>& factory)
{
    factory.addCreator("gradient", [](const Utils::ConfigNode& node) {
        return std::make_unique<Material::GradientColor>(node);
    });
}

RayTracer::Ltype type()
{
    return RayTracer::Ltype::MATERIAL;
}

const char* name()
{
    return "gradient";
}

}
