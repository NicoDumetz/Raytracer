/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "SFMLRenderer.hpp"

void Renderer::SFMLRenderer::openWindow(unsigned int width, unsigned int height, const Color &background)
{
    sf::VideoMode videoMode(width, height);
    _window.create(videoMode, "Raytracer", sf::Style::Default);
    _background = background;
}

void Renderer::SFMLRenderer::closeWindow()
{
    _window.close();
}

bool Renderer::SFMLRenderer::isOpen() const
{
    return _window.isOpen();
}

bool Renderer::SFMLRenderer::pollEvent()
{
    sf::Event event;
    if (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
        return true;
    }
    return false;
}

void Renderer::SFMLRenderer::clean()
{
    _window.clear(
        sf::Color({
            _background.r,
            _background.g,
            _background.b,
            _background.a
        }));
}

void Renderer::SFMLRenderer::drawPixelArray(const std::vector<std::vector<RayTracer::HitRecord>> &hitRecords)
{
    unsigned int imgWidth = hitRecords[0].size();
    unsigned int imgHeight = hitRecords.size();
    sf::Vector2u winSize = _window.getSize();
    sf::Vector2f scale(static_cast<float>(winSize.x) / imgWidth,
        static_cast<float>(winSize.y) / imgHeight);

    _image.create(imgWidth, imgHeight);
    for (unsigned int y = 0; y < imgHeight; ++y) {
        for (unsigned int x = 0; x < imgWidth; ++x) {
            const auto& c = hitRecords[y][x].getColor();
            _image.setPixel(x, y, sf::Color({
                c.r, c.g, c.b, c.a
            }));
        }
    }
    this->drawImage(scale);
}

void Renderer::SFMLRenderer::display()
{
    _window.display();
}

void Renderer::SFMLRenderer::drawImage(sf::Vector2f scale)
{
    sf::Texture texture;
    texture.loadFromImage(_image);

    sf::Sprite sprite(texture);
    sf::Vector2u winSize = _window.getSize();
    sprite.setScale(scale.x, scale.y);

    const_cast<sf::RenderWindow&>(_window).draw(sprite);
}

void Renderer::SFMLRenderer::saveImage(std::string path) const
{
    _image.saveToFile(path);
}
