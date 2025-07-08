/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include "AABB.hpp"

namespace Utils
{
bool AABB::intersect(const Ray &ray, double tMin, double tMax) const
{
    for (int i = 0; i < 3; i++) {
        double origin = ray.O[i];
        double direction = ray.D[i];

        if (direction == 0.0) {
            if (origin < _min[i] || origin > _max[i])
                return false;
        } else {
            double invD = 1.0 / direction;
            double t0 = (_min[i] - origin) * invD;
            double t1 = (_max[i] - origin) * invD;

            if (invD < 0.0) std::swap(t0, t1);

            tMin = (t0 > tMin) ? t0 : tMin;
            tMax = (t1 < tMax) ? t1 : tMax;

            if (tMax < tMin)
                return false;
        }
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
