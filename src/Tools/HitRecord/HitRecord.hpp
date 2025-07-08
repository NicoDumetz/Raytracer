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

namespace RayTracer
{
    class HitRecord {
        private:
            float distance;
            math::Point3D position;
            math::Vector3D normal;
            Color color;

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
        };
} // namespace RayTracer
