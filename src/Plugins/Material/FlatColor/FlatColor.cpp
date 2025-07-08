/*
** EPITECH PROJECT, 2025
** FlatColor.hpp
** File description:
** raytracer
*/

#include "FlatColor.hpp"

const Utils::Color& Material::FlatColor::shade(
    const Utils::HitRecord&,
    const Utils::Ray&,
    const RayTracer::Scene&
) const {
    return _color;
}

Material::FlatColor::FlatColor(const Utils::ConfigNode& node)
    : _color(node.parseColor("color"))
{
}