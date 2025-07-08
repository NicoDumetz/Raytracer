/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** LimitedCone
*/

#ifndef LIMITEDCONE_HPP_
#define LIMITEDCONE_HPP_

#include "Plugins/Primitives/APrimitives.hpp"


namespace Primitive {

    class LimitedCone : public APrimitive {
    public:
        LimitedCone(std::shared_ptr<Material::IMaterial> material,
                    math::Point3D center,
                    double radius,
                    double height,
                    double minY,
                    double maxY);
        LimitedCone(const Utils::ConfigNode& node);
            bool hit(const Utils::Ray& ray, Utils::HitRecord& record) const override;

        const Utils::AABB &getBoundingBox() const {return _box;};
    private:
        double _radius;
        double _height;
        double _minY;
        double _maxY;
        Utils::AABB _box;

        Utils::AABB calculateBox() const
        {
            double apexY = _position.y + _minY;
            double baseY = _position.y + _maxY;
            double baseRadius = _radius;
            math::Vector3D min = math::Vector3D(_position.x - baseRadius, apexY, _position.z - baseRadius);
            math::Vector3D max = math::Vector3D(_position.x + baseRadius, baseY, _position.z + baseRadius);

            return Utils::AABB(min, max);
        }
    };

    }

#endif /* !LIMITEDCONE_HPP_ */
