/*
** EPITECH PROJECT, 2025
** IPrimitive.hpp
** File description:
** Project
*/

#pragma once

#include "Tools/Ray/Ray.hpp"
#include "Tools/HitRecord/HitRecord.hpp"
#include "Tools/AABB/AABB.hpp"
#include "Tools/Math/Matrix/TransformMatrix.hpp"

namespace Primitive
{
    class IPrimitive {
    public:
        virtual ~IPrimitive() = default;
        virtual bool hit(const Utils::Ray& ray,  Utils::HitRecord& record) const = 0;
        virtual void applyTransform(const math::TransformMatrix &transform) = 0;
        virtual bool getBoundingBox(Utils::AABB &box) const = 0;
    };
} // namespace Raytracer

