/*
** EPITECH PROJECT, 2025
** IMaterial.hpp
** File description:
** Interface for materials in the raytracer
*/

#pragma once

#include "Tools/Ray/Ray.hpp"
#include "Tools/HitRecord/HitRecord.hpp"
#include "Tools/Color/Color.hpp"

namespace Material {
    class IMaterial {
    public:
    struct MaterialProperties {
        float   reflectivity    = 0.0f;
        float   transparency    = 0.0f;
        float   refractiveIndex = 1.0f;
    };
        virtual ~IMaterial() = default;
        virtual const Utils::Color &shade(const Utils::HitRecord& rec,
            const Utils::Ray& ray,
            MaterialProperties& props) const = 0;
    };
} // namespace RayTracer
