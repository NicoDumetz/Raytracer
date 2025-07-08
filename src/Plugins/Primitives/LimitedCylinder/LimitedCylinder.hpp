/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** LimitedCylinder
*/

#ifndef LIMITEDCYLINDER_HPP_
#define LIMITEDCYLINDER_HPP_
#pragma once

#include "Plugins/Primitives/APrimitives.hpp"

namespace Primitive {

class LimitedCylinder : public APrimitive {
public:
    LimitedCylinder(std::shared_ptr<Material::IMaterial> material,
                    math::Point3D center,
                    double radius,
                    double height,
                    double minY,
                    double maxY);
    LimitedCylinder(const Utils::ConfigNode& node);

    bool hit(const Utils::Ray& ray, Utils::HitRecord& record) const override;

private:
    double _radius;
    double _height;
    double _minY;
    double _maxY;
};

}


#endif /* !LIMITEDCYLINDER_HPP_ */
