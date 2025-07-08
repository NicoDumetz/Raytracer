/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once
#include "Interface/IRenderer.hpp"
#include "Tools/ConfigNode/ConfigNode.hpp"
#include "Shared/LibraryType.hpp"
#include "Factory/Factory.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace Renderer
{
    class SFMLRenderer : public Renderer::IRenderer
    {
        public:
            ~SFMLRenderer() = default;
            SFMLRenderer() = default;
            void openWindow(
                unsigned int width, unsigned int height, const Utils::Color &background = Utils::Color()) override;
            void closeWindow() override;

            bool isOpen() const override;
            bool pollEvent() override;

            void clean() override;
            void drawPixelArray(
                const std::vector<std::vector<Utils::Color>> &pixelsArray) override;
            void display();
            void saveImage(std::string path) const override;
        private:
            void drawImage(sf::Vector2f scale);
            sf::Image _image;
            sf::RenderWindow _window;
            Utils::Color _background;
    };
} // namespace Renderer
