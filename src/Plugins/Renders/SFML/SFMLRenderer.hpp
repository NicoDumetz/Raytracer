/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once
#include "Plugins/Renders/IRenderer.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace Renderer
{
    class SFMLRenderer
    {
        public:
            ~SFMLRenderer() = default;
            ~SFMLRenderer() = default;
            void openWindow(
                unsigned int width, unsigned int height, const Color &background = Color());
            void closeWindow();

            bool isOpen() const;
            bool pollEvent();

            void clean();
            void drawPixelArray(
                const std::vector<std::vector<RayTracer::HitRecord>> &pixelsArray);
            void display();
            void saveImage(std::string path) const;
        private:
            void drawImage(sf::Vector2f scale);
            sf::Image _image;
            sf::RenderWindow _window;
            Color _background;
    };
} // namespace Renderer
