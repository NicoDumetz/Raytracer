/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once

#include <cmath>
#include "Tools/Math/Point3D/Point3D.hpp"
#include "Tools/Math/Vector3D/Vector3D.hpp"
#include "Tools/Ray/Ray.hpp"
#include "Interface/ICamera.hpp"
#include "Tools/ConfigNode/ConfigNode.hpp"


namespace Cam
{
    class Camera : public ICamera {
        public:
        Camera(Resolution res,
            const math::Point3D& pos,
            const math::Point3D& lookAt,
            const math::Vector3D& up,
            float fov);
            Camera(const Utils::ConfigNode& node);

            Utils::Ray generateRay(int x, int y) const;
            const Resolution getResolution() const { return _resolution; }
            const math::Point3D& getPosition() const { return _position; }
        private:
            Resolution _resolution;
            math::Point3D _position;
            math::Vector3D _forward;
            math::Vector3D _up;
            math::Vector3D _right;
            float _fov;
    };
}

