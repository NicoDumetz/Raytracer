/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** DirectionnalLight.cpp
*/

#include "AmbientLight.hpp"

Utils::Color Light::AmbientLight::illuminate(const Utils::HitRecord&, const RayTracer::Scene&) const {
    return _intensity;
}

Light::AmbientLight::AmbientLight(const Utils::ConfigNode& node)
    : _intensity(node.parseColor("color"))
{
}
