/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#pragma once

#include "Tools/Color/Color.hpp"
#include "Tools/Math/Point3D/Point3D.hpp"
#include "Tools/Math/Vector3D/Vector3D.hpp"
#include "Tools/Ray/Ray.hpp"
#include <memory>

namespace Material {class IMaterial;}

namespace Utils
{
class AABB
{
public:
    AABB() = default;
    AABB(const math::Vector3D &a, const math::Vector3D &b) : _min(a), _max(b) {};
    ~AABB() = default;

    bool intersect(const Ray &ray,
        float tMin = 0.001f,
        float tMax = std::numeric_limits<float>::infinity()) const;

    AABB surroundingBox(const AABB& box0, const AABB& box1);

    const math::Vector3D &min() const {return _min;};
    const math::Vector3D &max() const {return _max;};
private:
    math::Vector3D _min;
    math::Vector3D _max;
};



} // namespace Utils
