/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** ALight.hpp - Classe de base pour lumières avec ombres douces optionnelles
*/

#pragma once

#include "Interface/ILight.hpp"
#include "Tools/Ray/Ray.hpp"
#include "RayTracer/Scene/Scene.hpp"
#include "Tools/ConfigNode/ConfigNode.hpp"
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

namespace Light {

    class ALight : public ILight {
    public:
        ALight(const Utils::Color& intensity,
               bool softShadow = false,
               float dispersion = 0.01f)
            : _intensity(intensity),
              _softShadow(softShadow),
              _dispersion(dispersion) {}

        virtual ~ALight() = default;

    protected:
        Utils::Color _intensity;
        bool _softShadow;
        float _dispersion;
        
        float computeSoftness(float distance) const {
            return std::clamp(distance * _dispersion, 0.0f, 1.0f);
        }
    };
} // namespace Light
