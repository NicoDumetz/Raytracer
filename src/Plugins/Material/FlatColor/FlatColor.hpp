/*
** EPITECH PROJECT, 2025
** FlatColor.hpp
** File description:
** raytracer
*/

#pragma once

#include "Interface/IMaterial.hpp"
#include "Tools/ConfigNode/ConfigNode.hpp"
#include "Shared/LibraryType.hpp"
#include "Factory/Factory.hpp"


namespace Material {

    class FlatColor : public IMaterial {
    private:
        Utils::Color _color;
    public:
        FlatColor(Utils::Color color =  Utils::Color()) : _color(color) {};
        FlatColor(const Utils::ConfigNode& node);
        ~FlatColor() = default;
        const Utils::Color& shade(
            const Utils::HitRecord &,
            const Utils::Ray &,
            IMaterial::MaterialProperties& props) const;
    };
} // namespace Material
