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
        const Utils::AABB getBoundingBox() const {return calculateBox();};
    private:
        math::Vector3D _normal;

        Utils::AABB calculateBox() const
        {
            const double k = 1e6;
            math::Vector3D n = _normal;
            math::Vector3D tangent;

            if (std::abs(n.x) < 1e-6 && std::abs(n.z) < 1e-6)
                tangent = math::Vector3D(1, 0, 0);
            else
                tangent = math::Vector3D(0, 1, 0);

            math::Vector3D u = n.cross(tangent).normalized();
            math::Vector3D v = n.cross(u).normalized();

            u *= k;
            v *= k;

            math::Point3D p0 = _position + u + v;
            math::Point3D p1 = _position + u - v;
            math::Point3D p2 = _position - u + v;
            math::Point3D p3 = _position - u - v;

            double minX = std::min({p0.x, p1.x, p2.x, p3.x});
            double minY = std::min({p0.y, p1.y, p2.y, p3.y});
            double minZ = std::min({p0.z, p1.z, p2.z, p3.z});
            double maxX = std::max({p0.x, p1.x, p2.x, p3.x});
            double maxY = std::max({p0.y, p1.y, p2.y, p3.y});
            double maxZ = std::max({p0.z, p1.z, p2.z, p3.z});

            math::Vector3D delta = n * 0.01;
            math::Vector3D boxMin = math::Vector3D(minX, minY, minZ) + delta * - 1;
            math::Vector3D boxMax = math::Vector3D(maxX, maxY, maxZ) + delta;

            return Utils::AABB(boxMin, boxMax);
        }

    };
}
