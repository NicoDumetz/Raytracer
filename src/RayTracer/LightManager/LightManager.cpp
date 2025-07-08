/*
** EPITECH PROJECT, 2025
** APrimitive.hpp
** File description:
** Project
*/

// LightManager.cpp
#include "LightManager.hpp"
#include <algorithm>
#include <cmath>

namespace RayTracer {

std::optional<math::Vector3D> LightManager::refract(
    const math::Vector3D& I,
    const math::Vector3D& N,
    float eta
) {
    float cosi = std::clamp(static_cast<float>(I.dot(N)), -1.0f, 1.0f);
    float etai = 1.0f, etat = eta;
    math::Vector3D n = N;
    if (cosi < 0.0f) {
        cosi = -cosi;
    } else {
        std::swap(etai, etat);
        n = -N;
    }
    float k = 1.0f - (etai/etat)*(etai/etat)*(1.0f - cosi*cosi);
    if (k < 0.0f)
        return std::nullopt;  // réflexion totale interne
    return (I*(etai/etat) + n*(etai/etat * cosi - std::sqrt(k))).normalized();
}

Utils::Color LightManager::computeDirectLighting(
    const Utils::HitRecord& hit,
    const Scene& scene
) const {
    Utils::Color sum(0.0f, 0.0f, 0.0f, 1.0f);
    for (const auto& light : scene.getLights()) {
        sum += light->illuminate(hit, scene);
    }
    // clamp
    sum.r = std::clamp(sum.r, 0.0f, 1.0f);
    sum.g = std::clamp(sum.g, 0.0f, 1.0f);
    sum.b = std::clamp(sum.b, 0.0f, 1.0f);
    return sum;
}

Utils::Color LightManager::traceRay(
    const Utils::Ray& ray,
    const Scene& scene,
    int depth
) const {
    constexpr int   MAX_DEPTH = 5;
    constexpr float EPS       = 1e-4f;

    if (depth > MAX_DEPTH)
        return scene.getBackgroundColor();

    Utils::HitRecord record;
    if (!scene.trace(ray, record))
        return scene.getBackgroundColor();

    Material::IMaterial::MaterialProperties props{};
    Utils::Color albedo = record
        .getMaterial()
        .shade(record, ray, props);

    Utils::Color direct = computeDirectLighting(record, scene);
    Utils::Color localColor = {
        albedo.r * direct.r,
        albedo.g * direct.g,
        albedo.b * direct.b,
        albedo.a
    };

    math::Vector3D N = record.getNormal().normalized();
    math::Vector3D V = -ray.getDirection().normalized();

    Utils::Color reflColor(0,0,0,1), refrColor(0,0,0,1);
    if (props.reflectivity > 0.0f) {
        math::Vector3D R = V - (N * 2.0f * (V.dot(N)));
        Utils::Ray reflRay(record.getPosition() + N*EPS, R);
        reflColor = traceRay(reflRay, scene, depth + 1)
                  * props.reflectivity;
    }
    if (props.transparency > 0.0f) {
        float eta = (V.dot(N) > 0.0f)
                  ? (1.0f/props.refractiveIndex)
                  : props.refractiveIndex;
        if (auto refrDir = refract(V, N, eta)) {
            Utils::Ray refrRay(record.getPosition() - N*EPS, *refrDir);
            refrColor = traceRay(refrRay, scene, depth + 1)
                      * props.transparency;
        }
    }
    return localColor + reflColor + refrColor;
}

} // namespace RayTracer
