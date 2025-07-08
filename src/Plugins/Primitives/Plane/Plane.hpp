/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once

#include "Tools/Math/Point3D/Point3D.hpp"
#include "Tools/Math/Vector3D/Vector3D.hpp"
#include "Tools/Ray/Ray.hpp"
#include "Tools/HitRecord/HitRecord.hpp"
#include "Plugins/Primitives/APrimitives.hpp"

namespace Primitive
{
    class Plane : public APrimitive
    {
    public:
        Plane(std::shared_ptr<Material::IMaterial> material,
              math::Point3D point,
              math::Vector3D normal);
        ~Plane() = default;

        bool hit(const Utils::Ray &ray, Utils::HitRecord &record) const override;
        void applyTransform(const math::TransformMatrix &transform) override;

    private:
        math::Vector3D _normal;
    };
}
