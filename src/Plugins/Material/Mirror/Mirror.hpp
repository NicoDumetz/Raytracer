/*
** EPITECH PROJECT, 2025
** Mirror.hpp
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

    class Mirror : public IMaterial {
    private:
        Utils::Color _color;
    public:
        Mirror(Utils::Color color = Utils::Color());
        Mirror(const Utils::ConfigNode& node);
        ~Mirror() = default;

        const Utils::Color& shade(
            const Utils::HitRecord&,
            const Utils::Ray&,
            IMaterial::MaterialProperties& props) const override;
    };
} // namespace Material