/*
** EPITECH PROJECT, 2025
** APrimitive.hpp
** File description:
** Project
*/


#pragma once
#include <functional>
#include <unordered_map>
#include <memory>
#include "Tools/ConfigNode/ConfigNode.hpp"

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

        using TransformFn = std::function<void(math::TransformMatrix&, const Utils::ConfigNode&)>;
        const std::unordered_map<std::string, TransformFn> _transformHandler = {
            {"translate", [](math::TransformMatrix& T, const Utils::ConfigNode& node) {
                T.applyTranslation(node.parseVector3("translate"));
            }},
            {"rotateX", [](math::TransformMatrix& T, const Utils::ConfigNode& node) {
                T.applyRotationX(node.parseFloat("rotateX") * M_PI / 180.0f);
            }},
            {"rotateY", [](math::TransformMatrix& T, const Utils::ConfigNode& node) {
                T.applyRotationY(node.parseFloat("rotateY") * M_PI / 180.0f);
            }},
            {"rotateZ", [](math::TransformMatrix& T, const Utils::ConfigNode& node) {
                T.applyRotationZ(node.parseFloat("rotateZ") * M_PI / 180.0f);
            }}
        };
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
        void applyNodeTransform(const Utils::ConfigNode& node)
        {
            math::TransformMatrix T;

            for (const auto& [key, fn] : _transformHandler) {
                if (node.has(key))
                    fn(T, node);
            }
            applyTransform(T);
        }

    };
} // namespace Raytracer