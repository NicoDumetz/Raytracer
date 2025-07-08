/*
** EPITECH PROJECT, 2025
** Glass.hpp
** File description:
** raytracer
*/

#include "Glass.hpp"

namespace Material
{

    Glass::Glass(const Utils::ConfigNode& node)
        : _color(node.parseColor("color")),
          _ior(node.parseFloat("ior"))
    {
        if (_ior <= 0)
            throw std::invalid_argument("Invalid IOR value");
    }

    const Utils::Color& Glass::shade(const Utils::HitRecord &rec,
        const Utils::Ray &ray,
        IMaterial::MaterialProperties &props) const{
        float cosTheta = std::fabs(
            ray.getDirection().normalized()
            .dot(rec.getNormal().normalized())
        );
        float r0 = std::pow((1.0f - _ior) / (1.0f + _ior), 2.0f);
        props.reflectivity    = r0 + (1.0f - r0) * std::pow(1 - cosTheta, 5);
        props.transparency    = 1.0f - props.reflectivity;
        props.refractiveIndex = _ior;
        return _color;
    }
} // namespace Material

extern "C" {

    void registerPlugin(RayTracer::Factory<Material::IMaterial>& factory)
    {
        factory.addCreator("glass", [](const Utils::ConfigNode& node) {
            return std::make_unique<Material::Glass>(node);
        });
    }

    RayTracer::Ltype type()
    {
        return RayTracer::Ltype::MATERIAL;
    }

    const char* name()
    {
        return "glass";
    }

}