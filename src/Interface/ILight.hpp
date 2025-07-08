/*
** EPITECH PROJECT, 2025
** ILight.hpp
** File description:
** Project
*/

#pragma once

#include "Tools/Color/Color.hpp"
#include "Tools/Math/Point3D/Point3D.hpp"
#include "Tools/Math/Vector3D/Vector3D.hpp"
#include "Tools/HitRecord/HitRecord.hpp"

namespace RayTracer {
    class Scene;
}

namespace Light {
    class ILight {
    public:
        virtual ~ILight() = default;

        virtual Utils::Color illuminate(const Utils::HitRecord& hit, const RayTracer::Scene& scene) const = 0;
    };
}
