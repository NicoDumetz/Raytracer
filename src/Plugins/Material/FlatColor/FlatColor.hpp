/*
** EPITECH PROJECT, 2025
** FlatColor.hpp
** File description:
** raytracer
*/

#pragma once

#include "Tools/Ray/Ray.hpp"
#include "Tools/HitRecord/HitRecord.hpp"
#include "Tools/Color/Color.hpp"
#include "Interface/IMaterial.hpp"
#include "Tools/ConfigNode/ConfigNode.hpp"


namespace Material {

    class FlatColor : public IMaterial{
    private:
        Utils::Color _color;
    public:
        FlatColor( Utils::Color color =  Utils::Color()) : _color(color) {};
        FlatColor(const Utils::ConfigNode& node);
        ~FlatColor() = default;
        const Utils::Color& shade(const Utils::HitRecord&,
            const Utils::Ray&,
            const RayTracer::Scene&) const;
    };
} // namespace Material
