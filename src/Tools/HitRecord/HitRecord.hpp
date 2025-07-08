/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#pragma once

#include "Tools/Color/Color.hpp"
#include "Tools/Math/Point3D/Point3D.hpp"
#include "Tools/Math/Vector3D/Vector3D.hpp"
#include <memory>

namespace Material {
    class IMaterial;
}

namespace Utils
{
    class HitRecord {
        private:
            float distance;
            math::Point3D position;
            math::Vector3D normal;
            Color color;
            std::shared_ptr<Material::IMaterial> _material;

        public:
            HitRecord() = default;
            ~HitRecord() = default;

            HitRecord(float dist, const math::Point3D& pos, const math::Vector3D& nrm, const Color& col)
                : distance(dist), position(pos), normal(nrm), color(col) {}

            float getDistance() const { return distance; }
            void setDistance(float dist) { distance = dist; }

            const math::Point3D& getPosition() const { return position; }
            void setPosition(const math::Point3D& pos) { position = pos; }

            const math::Vector3D& getNormal() const { return normal; }
            void setNormal(const math::Vector3D& nrm) { normal = nrm; }

            const Color& getColor() const { return color; }
            void setColor(const Color& col) { color = col; }

            Material::IMaterial& getMaterial() { return *_material; }
            void setMaterial(std::shared_ptr<Material::IMaterial> material) {_material = std::move(material);};
        };
} // namespace Utils
