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
#include "Cylinder.hpp"
#include <cmath>

namespace Primitive {

    class Cylinder : public APrimitive {
    public:
        Cylinder(std::shared_ptr<Material::IMaterial> material,
                 math::Point3D base,
                 double height,
                 double radius);
    
        Cylinder(const Utils::ConfigNode& node);
        ~Cylinder() override = default;
    
        bool hit(const Utils::Ray& ray, Utils::HitRecord& record) const override;
        bool topCapHit(const Utils::Ray &ray,
            Utils::HitRecord &record,
            const Utils::Ray &localRay,
            const math::Vector3D &d) const;
        bool botCapHit(const Utils::Ray &ray,
            Utils::HitRecord &record,
            const Utils::Ray &localRay,
            const math::Vector3D &d) const;
    private:
        math::Point3D _base;
        double _height;
        double _radius;
    };
} // namespace Primitive