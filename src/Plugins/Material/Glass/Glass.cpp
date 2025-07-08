/*
** EPITECH PROJECT, 2025
** Glass.hpp
** File description:
** raytracer
*/

#include "Glass.hpp"

namespace Material
{
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
