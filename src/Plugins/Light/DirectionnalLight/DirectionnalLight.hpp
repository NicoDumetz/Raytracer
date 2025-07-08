/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** DirectionnalLight.cpp
*/

#pragma once

#include "Interface/ILight.hpp"
#include "Tools/Ray/Ray.hpp"
#include "RayTracer/Scene/Scene.hpp"
#include <cmath>
#include "Tools/ConfigNode/ConfigNode.hpp"

namespace Light {

    class DirectionalLight : public ILight {
    public:
        DirectionalLight(const math::Vector3D& direction, const Utils::Color& intensity)
            : _direction(direction.normalized()), _intensity(intensity) {}
        DirectionalLight(const Utils::ConfigNode& node);
        Utils::Color illuminate(const Utils::HitRecord& hit, const RayTracer::Scene& scene) const;
    private:
        math::Vector3D _direction;
        Utils::Color _intensity;
    };
} // namespace Light