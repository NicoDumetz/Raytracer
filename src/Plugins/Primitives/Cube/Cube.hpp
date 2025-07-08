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

        const Utils::AABB getBoundingBox() const {return calculateBox();};
    private:
        double _halfSize;

    Utils::AABB calculateBox() const
    {
        math::Vector3D positionVec = math::Vector3D(_position.x, _position.y, _position.z);
        math::Vector3D min = positionVec - math::Vector3D(_halfSize, _halfSize, _halfSize);
        math::Vector3D max = positionVec + math::Vector3D(_halfSize, _halfSize, _halfSize);

        return Utils::AABB(min, max);
    }
    };
}

#endif /* !TANGLESCUBES_HPP_ */
