/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include "AABB.hpp"

namespace Utils
{
bool AABB::intersect(const Ray &ray, float tMin, float tMax) const
{
    double t0;
    double t1;
    float invD;

    for (int i = 0; i < 3; i++) {
        invD = 1.0f / ray.D[i];
        t0 = (_min[i] - ray.O[i] * invD);
        t1 = (_max[i] - ray.O[i] * invD);
        if (invD < 0.0f) std::swap(t0, t1);
        tMin = std::max(static_cast<double>(tMin), t0);
        tMax = std::max(static_cast<double>(tMax), t1);
        if (tMax <= tMin) return false;
    }
    return true;
}

AABB AABB::surroundingBox(const AABB &box0, const AABB &box1)
{
    return AABB(
        math::Vector3D(
            std::min(box0._min.x, box1._min.x),
            std::min(box0._min.y, box1._min.y),
            std::min(box0._min.z, box1._min.z)
        ),
        math::Vector3D(
            std::max(box0._max.x, box1._max.x),
            std::max(box0._max.y, box1._max.y),
            std::max(box0._max.z, box1._max.z)
        )
    );
}

} // namespace Utils
