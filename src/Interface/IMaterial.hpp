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
#include "RayTracer/Scene/Scene.hpp"

namespace Material {
    class IMaterial {
    public:
        virtual ~IMaterial() = default;
        virtual const Utils::Color& shade(const Utils::HitRecord& record,
                            const Utils::Ray& ray,
                            const RayTracer::Scene& scene) const = 0;
    };
} // namespace RayTracer
