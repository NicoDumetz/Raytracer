/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** TanglesCubes
*/

#ifndef TANGLESCUBES_HPP_
#define TANGLESCUBES_HPP_

#include "Plugins/Primitives/APrimitives.hpp"

namespace Primitive {

    class Cube : public APrimitive {
    public:
        Cube(std::shared_ptr<Material::IMaterial> material,
             math::Point3D center,
             double size);

        Cube(const Utils::ConfigNode& node);

        bool hit(const Utils::Ray& ray, Utils::HitRecord& record) const override;

    private:
        double _halfSize;
    };
}

#endif /* !TANGLESCUBES_HPP_ */
