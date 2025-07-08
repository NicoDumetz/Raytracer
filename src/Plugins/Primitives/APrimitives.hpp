/*
** EPITECH PROJECT, 2025
** APrimitive.hpp
** File description:
** Project
*/


#pragma once

#include <memory>
#include "Tools/Ray/Ray.hpp"
#include "Tools/HitRecord/HitRecord.hpp"
#include "Interface/IPrimitive.hpp"
#include "Interface/IMaterial.hpp"
#include "Tools/Math/Point3D/Point3D.hpp"
#include "Tools/Math/Matrix/TransformMatrix.hpp"

namespace Primitive
{
    class APrimitive : public IPrimitive {
    protected:
        math::TransformMatrix _transform;
        math::TransformMatrix _inverseTransform;
        std::shared_ptr<Material::IMaterial> _material;
        math::Point3D _position;
    public:
        APrimitive(std::shared_ptr<Material::IMaterial> material, math::Point3D position) 
            : _material(std::move(material)), _position(position) {};
        ~APrimitive() = default;
        const Material::IMaterial &getMaterial() const { return *_material; }
        void setMaterial(std::shared_ptr<Material::IMaterial> material) {
            _material = std::move(material);
        }
        const math::Point3D& getPosition() const { return _position; }
        void setPosition(const math::Point3D& pos) { _position = pos; }
        virtual bool hit(const Utils::Ray& ray, Utils::HitRecord& record) const = 0;
        virtual void applyTransform(const math::TransformMatrix& M) {
            _transform = M * _transform;
            _inverseTransform = _transform.inverse();
        }
        
    };
} // namespace Raytracer