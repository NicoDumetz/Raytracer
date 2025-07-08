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
    const Utils::Color baseColor = hit.getMaterial().shade(hit, ray, scene);

    Utils::Color diffuseSum(0.0f, 0.0f, 0.0f, 1.0f);
    for (const auto& light : scene.getLights())
        diffuseSum += light->illuminate(hit, scene);
    diffuseSum.r = std::clamp(diffuseSum.r, 0.0f, 1.0f);
    diffuseSum.g = std::clamp(diffuseSum.g, 0.0f, 1.0f);
    diffuseSum.b = std::clamp(diffuseSum.b, 0.0f, 1.0f);

    return Utils::Color(
        baseColor.r * diffuseSum.r,
        baseColor.g * diffuseSum.g,
        baseColor.b * diffuseSum.b,
        baseColor.a
    );
}

