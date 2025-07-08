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

    private:
        double _radius;
        double _height;
        double _minY;
        double _maxY;
    };

    }

#endif /* !LIMITEDCONE_HPP_ */
