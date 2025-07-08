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
        return std::nullopt;
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
    sum.r = std::clamp(sum.r, 0.0f, 1.0f);
    sum.g = std::clamp(sum.g, 0.0f, 1.0f);
    sum.b = std::clamp(sum.b, 0.0f, 1.0f);
    return sum;
}

Utils::Color LightManager::traceRay(
    const Utils::Ray& ray,
    const Scene&      scene,
    int               depth
) const {
    constexpr int   MAX_DEPTH = 4;
    constexpr float EPS       = 1e-4f;

    if (depth > MAX_DEPTH)
        return scene.getBackgroundColor();

    Utils::HitRecord rec;
    if (!scene.trace(ray, rec))
        return scene.getBackgroundColor();

    Material::IMaterial::MaterialProperties props{};
    Utils::Color albedo = rec.getMaterial()
        .shade(rec, ray, props);

    math::Vector3D N = rec.getNormal().normalized();
    math::Vector3D D = ray.getDirection().normalized();
    if (D.dot(N) > 0.0f) 
        N = -N;

    if (props.reflectivity >= 1.0f - 1e-6f && props.transparency <= 1e-6f) {
        math::Vector3D R = D.reflect(N);
        Utils::Ray reflRay(rec.getPosition() + N*EPS, R);
        return traceRay(reflRay, scene, depth+1) * albedo;
    }

    Utils::Color direct = computeDirectLighting(rec, scene);
    Utils::Color local  = {
        albedo.r * direct.r,
        albedo.g * direct.g,
        albedo.b * direct.b,
        albedo.a
    };

    Utils::Color reflColor(0,0,0,1);
    if (props.reflectivity > 0.0f) {
        math::Vector3D R = D.reflect(N);
        Utils::Ray reflRay(rec.getPosition() + N*EPS, R);
        reflColor = traceRay(reflRay, scene, depth+1)
                  * props.reflectivity;
    }

    Utils::Color refrColor(0,0,0,1);
    if (props.transparency > 0.0f) {
        if (auto T = refract(D, N, props.refractiveIndex)) {
            Utils::Ray refrRay(rec.getPosition() + *T * EPS, *T);
            refrColor = traceRay(refrRay, scene, depth)
          * props.transparency
          * albedo;

        }
    }
    Utils::Color result = local + reflColor + refrColor;
    result.r = std::clamp(result.r, 0.0f, 1.0f);
    result.g = std::clamp(result.g, 0.0f, 1.0f);
    result.b = std::clamp(result.b, 0.0f, 1.0f);
    return result;

}
}
