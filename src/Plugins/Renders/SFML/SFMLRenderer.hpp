/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once
#include "Interface/IRenderer.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace Renderer
{
    class SFMLRenderer
    {
        public:
            ~SFMLRenderer() = default;
            SFMLRenderer() = default;
            void openWindow(
                unsigned int width, unsigned int height, const Utils::Color &background = Utils::Color());
            void closeWindow();

            bool isOpen() const;
            bool pollEvent();

            void clean();
            void drawPixelArray(
                const std::vector<std::vector<Utils::Color>> &pixelsArray);
            void display();
            void saveImage(std::string path) const;
        private:
            void drawImage(sf::Vector2f scale);
            sf::Image _image;
            sf::RenderWindow _window;
            Utils::Color _background;
    };
} // namespace Renderer
