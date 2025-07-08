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
    class Sphere : public APrimitive
    {
        public:
            Sphere(std::shared_ptr<Material::IMaterial> material,
                math::Point3D center,
                double radius);
            Sphere(const Utils::ConfigNode& node);

            ~Sphere() = default;
            bool hit(const Utils::Ray &, Utils::HitRecord &) const;
            bool hitSphere(Utils::Ray localRay,
                Utils::HitRecord &record,
                double t,
                const Utils::Ray &ray) const;
            Utils::AABB &getBoundingBox() const;
        private:
            double _radius;
            Utils::AABB _box;

            Utils::AABB calculateBox() const {
                math::Vector3D min(_position.x - _radius, _position.y - _radius, _position.z - _radius);
                math::Vector3D max(_position.x + _radius, _position.y + _radius, _position.z + _radius);
                return Utils::AABB(min, max);
            }
    };
} // namespace RayTracer
