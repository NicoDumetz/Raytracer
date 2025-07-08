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

