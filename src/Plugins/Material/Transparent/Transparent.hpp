/*
** EPITECH PROJECT, 2025
** Transparent.hpp
** File description:
** raytracer
*/

#pragma once

#include "Interface/IMaterial.hpp"
#include "Tools/Color/Color.hpp"
#include "Tools/ConfigNode/ConfigNode.hpp"
#include "Shared/LibraryType.hpp"
#include "Factory/Factory.hpp"

namespace Material {

    class Transparent : public IMaterial {
    private:
        Utils::Color _color;
    public:
        Transparent(Utils::Color color = Utils::Color());
        Transparent(const Utils::ConfigNode& node);
        ~Transparent() = default;

        const Utils::Color& shade(
            const Utils::HitRecord&,
            const Utils::Ray&,
            IMaterial::MaterialProperties& props) const override;
    };
} // namespace Material