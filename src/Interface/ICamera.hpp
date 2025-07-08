/*
** EPITECH PROJECT, 2025
** ICamera.hpp
** File description:
** Project
*/

#pragma once

#include "Tools/Ray/Ray.hpp"

namespace Cam
{
    class ICamera {
        public:
        struct Resolution {
            int width;
            int height;
        };
        public:
            virtual ~ICamera() = default;
            virtual Utils::Ray generateRay(int x, int y) const = 0;
            virtual const Resolution getResolution() const = 0;
        };
} // namespace Cam
