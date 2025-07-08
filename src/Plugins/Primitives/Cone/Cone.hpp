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
#include "Tools/ConfigNode/ConfigNode.hpp"
#include "Shared/LibraryType.hpp"
#include "Factory/Factory.hpp"

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
        bool hitCone(
                const Utils::Ray &ray,
                Utils::HitRecord &record,
                const math::Point3D &localHit) const;

        const Utils::AABB getBoundingBox() const {return calculateBox();};
    private:
        math::Point3D _apex;
        double _height;
        double _radius;

        Utils::AABB calculateBox() const
        {
            double minX = -_radius;
            double maxX = _radius;
            double minY = 0;
            double maxY = _height;
            double minZ = -_radius;
            double maxZ = _radius;

            math::Vector3D min(minX, minY, minZ);
            math::Vector3D max(maxX, maxY, maxZ);

            return Utils::AABB(min, max);
        }
    };
} // namespace Primitive
