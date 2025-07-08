/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once
#include "Tools/HitRecord/HitRecord.hpp"
#include "Tools/Color/Color.hpp"
#include <vector>
#include <string>

namespace Renderer
{
    class IRenderer
    {
        public:
        virtual ~IRenderer() = default;
        virtual void openWindow(
            unsigned int width, unsigned int height, const Utils::Color &background) = 0;
        virtual void closeWindow() = 0;

        virtual bool isOpen() const = 0;
        virtual bool pollEvent() = 0;

        virtual void clean() = 0;
        virtual void drawPixelArray(
            const std::vector<std::vector<Utils::Color>> &pixelsArray) = 0;
        virtual void display() = 0;
        virtual void saveImage(std::string path) const = 0;
    };
} // namespace Renderer
