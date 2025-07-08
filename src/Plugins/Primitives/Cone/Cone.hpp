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
#include <limits>
#include <cmath>

namespace Primitive {
    class Cone : public APrimitive {
    public:
        Cone(std::shared_ptr<Material::IMaterial> material,
             math::Point3D apex,
             double height,
             double radius);
        Cone(const Utils::ConfigNode& node);

        ~Cone() = default;

        bool hit(const Utils::Ray& ray, Utils::HitRecord& record) const override;
        bool hitBottomCap(
                const Utils::Ray &ray,
                Utils::HitRecord &record,
                const Utils::Ray &localRay,
                const math::Vector3D &d) const;
    private:
        math::Point3D _apex;
        double _height;
        double _radius;
    };
} // namespace Primitive
