/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** Torus
*/

#pragma once

#include "Plugins/Primitives/APrimitives.hpp"

namespace Primitive {

class Torus : public APrimitive {
public:
    Torus(std::shared_ptr<Material::IMaterial> material,
          math::Point3D center, double majorRadius, double minorRadius);
    Torus(const Utils::ConfigNode& node);

    bool hit(const Utils::Ray& ray, Utils::HitRecord& record) const override;


private:
double _majorRadius;
double _minorRadius;
    std::vector<double> solveQuartic(double A, double B, double C, double D, double E) const;
    std::vector<double> intersectTorusBody(const Utils::Ray& localRay) const;
};

}
