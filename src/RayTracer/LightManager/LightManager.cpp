/*
** EPITECH PROJECT, 2025
** APrimitive.hpp
** File description:
** Project
*/

#include "LightManager.hpp"
#include <iostream>

Utils::Color RayTracer::LightManager::computeLighting(Utils::HitRecord& hit, const RayTracer::Scene& scene, const Utils::Ray &ray) const {
    Utils::Color lightSum(0, 0, 0, 255);

    for (const auto& light : scene.getLights()) {
        Utils::Color contribution = light->illuminate(hit, scene);
        lightSum.r = std::min(1.0f, lightSum.r + contribution.r);
        lightSum.g = std::min(1.0f, lightSum.g + contribution.g);
        lightSum.b = std::min(1.0f, lightSum.b + contribution.b);
    }
    const Utils::Color& baseColor = hit.getMaterial().shade(hit, ray, scene);
    return Utils::Color(
        baseColor.r * lightSum.r,
        baseColor.g * lightSum.g,
        baseColor.b * lightSum.b,
        255
    );
    
}
