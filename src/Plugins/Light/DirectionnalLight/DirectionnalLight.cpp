/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** DirectionnalLight.cpp
*/

#include "DirectionnalLight.hpp"
#include <iostream>

Utils::Color Light::DirectionalLight::illuminate(const Utils::HitRecord& hit, const RayTracer::Scene& scene) const {
    math::Point3D point = hit.getPosition();
    math::Vector3D normal = hit.getNormal();
    math::Vector3D lightDir = - _direction.normalized();

    const double epsilon = 1e-4;
    math::Point3D shadowOrigin = point + lightDir * epsilon;
    Utils::Ray shadowRay(shadowOrigin, lightDir);
    Utils::HitRecord shadowHit;

    if (scene.trace(shadowRay, shadowHit))
        return Utils::Color(0, 0, 0, 1.0f);
    float dot = std::max(static_cast<double>(0.0f), normal.dot(lightDir));
        
        return Utils::Color(
            _intensity.r * dot,
            _intensity.g * dot,
            _intensity.b * dot,
            1.0f
        );
        
}
