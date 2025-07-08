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

    class Cylinder : public APrimitive {
    public:
        Cylinder(std::shared_ptr<Material::IMaterial> material,
                 math::Point3D base,
                 double radius);
    
        Cylinder(const Utils::ConfigNode& node);
        ~Cylinder() override = default;
    
        bool hit(const Utils::Ray& ray, Utils::HitRecord& record) const override;
        bool cylinderHit(Utils::Ray localRay,
            const Utils::Ray& ray,
            Utils::HitRecord& record,
            double t) const;

        const Utils::AABB getBoundingBox() const {return calculateBox();};
    private:
        math::Point3D _base;
        double _radius;

        Utils::AABB calculateBox() const
        {
            math::Vector3D baseVec = math::Vector3D(_base.x, _base.y, _base.z);
            double height = 2 * _radius;
            math::Vector3D min = baseVec - math::Vector3D(_radius, 0, _radius);
            math::Vector3D max = baseVec + math::Vector3D(_radius, height, _radius);

            return Utils::AABB(min, max);
        }
    };
} // namespace Primitive