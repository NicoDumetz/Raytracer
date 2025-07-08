/*
** EPITECH PROJECT, 2025
** APrimitive.hpp
** File description:
** Project
*/

#pragma once
#include "Tools/Color/Color.hpp"
#include "Tools/Math/Point3D/Point3D.hpp"
#include "Interface/IMaterial.hpp"
#include "RayTracer/Scene/Scene.hpp"
#include "Tools/HitRecord/HitRecord.hpp"
#include <algorithm>

namespace RayTracer
{
    class LightManager {
        public:
            Utils::Color computeLighting(
                Utils::HitRecord &recorder,
                const RayTracer::Scene& scene,
                const Utils::Ray &ray
            ) const;
        };
} // namespace RayTracer
