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
#include "Tools/ConfigNode/ConfigNode.hpp"
#include "Shared/LibraryType.hpp"
#include "Factory/Factory.hpp"

namespace Primitive
{
    class Plane : public APrimitive
    {
    public:
        Plane(std::shared_ptr<Material::IMaterial> material,
              math::Point3D point,
              math::Vector3D normal);
        Plane(const Utils::ConfigNode& node);
        ~Plane() = default;

        bool hit(const Utils::Ray &ray, Utils::HitRecord &record) const override;
    private:
        math::Vector3D _normal;
    };
}
