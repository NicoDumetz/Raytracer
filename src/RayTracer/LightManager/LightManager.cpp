/*
** EPITECH PROJECT, 2025
** APrimitive.hpp
** File description:
** Project
*/

#include "LightManager.hpp"
#include <iostream>

Utils::Color RayTracer::LightManager::computeLighting(
    Utils::HitRecord& hit,
    const RayTracer::Scene& scene,
    const Utils::Ray& ray
) const {
    Utils::Color lightSum(0.0f, 0.0f, 0.0f, 1.0f);

    for (const auto& light : scene.getLights()) {
        Utils::Color contribution = light->illuminate(hit, scene);
        lightSum.r += contribution.r;
        lightSum.g += contribution.g;
        lightSum.b += contribution.b;
    }

    lightSum.r = std::clamp(lightSum.r, 0.0f, 1.0f);
    lightSum.g = std::clamp(lightSum.g, 0.0f, 1.0f);
    lightSum.b = std::clamp(lightSum.b, 0.0f, 1.0f);

    const Utils::Color& baseColor = hit.getMaterial().shade(hit, ray, scene);

    return Utils::Color(
        baseColor.r * lightSum.r,
        baseColor.g * lightSum.g,
        baseColor.b * lightSum.b,
        baseColor.a
    );
}
