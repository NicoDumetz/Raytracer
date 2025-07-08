/*
** EPITECH PROJECT, 2025
** Glass.hpp
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

    class Glass : public IMaterial{
    private:
        Utils::Color _color;
        float _ior;
    public:
        Glass( Utils::Color color =  Utils::Color(), float ior = 0) : _color(color), _ior(ior) {};
        Glass(const Utils::ConfigNode& node);
        ~Glass() = default;
        const Utils::Color &shade(
            const Utils::HitRecord &,
            const Utils::Ray &,
            IMaterial::MaterialProperties& props) const;
    };
} // namespace Material