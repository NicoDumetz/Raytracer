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
    private:
        math::Point3D _base;
        double _radius;
    };
} // namespace Primitive