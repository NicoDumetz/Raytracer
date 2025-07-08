/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** DirectionnalLight.cpp
*/

#pragma once

#include "Interface/ILight.hpp"

namespace Light {

    class AmbientLight : public ILight {
    public:
        AmbientLight(const Utils::Color& intensity)
            : _intensity(intensity) {}
        Utils::Color illuminate(const Utils::HitRecord& hit, const RayTracer::Scene& scene) const;
    private:
        Utils::Color _intensity;
    };

} // namespace Light