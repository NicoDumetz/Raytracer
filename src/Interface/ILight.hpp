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

namespace RayTracer
{
    class ILight {
    public:
        virtual ~ILight() = default;

        virtual math::Vector3D getDirection(const math::Point3D& point) const = 0;
        virtual Color getIntensity(const math::Point3D& point) const = 0;
    };
}
