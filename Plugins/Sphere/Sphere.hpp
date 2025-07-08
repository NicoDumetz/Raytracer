/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once

#include "Tools/Math/Point3D/Point3D.hpp"
#include "Tools/Math/Vector3D/Vector3D.hpp"
#include "RayTracer/Ray/Ray.hpp"
#include "Interface/IPrimitive.hpp"
#include "Tools/HitRecord/HitRecord.hpp"

namespace RayTracer
{
    class Sphere : public IPrimitive
    {
        public:
            Sphere(math::Point3D center, double radius);
            ~Sphere() = default;
            bool hit(const Ray &, HitRecord &) const;
        private:
            math::Point3D _center;
            double R;
    };
} // namespace RayTracer
