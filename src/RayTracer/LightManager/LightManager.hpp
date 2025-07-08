/*
** EPITECH PROJECT, 2025
** APrimitive.hpp
** File description:
** Project
*/

#pragma once

#include <optional>
#include "Tools/Ray/Ray.hpp"
#include "Tools/HitRecord/HitRecord.hpp"
#include "Tools/Color/Color.hpp"
#include "RayTracer/Scene/Scene.hpp"
#include "Interface/IMaterial.hpp"

namespace RayTracer {

class LightManager {
public:
    struct MaterialProperties {
        float reflectivity    = 0.0f;
        float transparency    = 0.0f;
        float refractiveIndex = 1.0f;
    };

    static std::optional<math::Vector3D> refract(
        const math::Vector3D& I,
        const math::Vector3D& N,
        float eta
    );

    Utils::Color computeDirectLighting(
        const Utils::HitRecord& hit,
        const Scene& scene
    ) const;

    Utils::Color traceRay(
        const Utils::Ray& ray,
        const Scene& scene,
        int depth = 0
    ) const;
};

} // namespace RayTracer

