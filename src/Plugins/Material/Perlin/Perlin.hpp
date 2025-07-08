/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** Perlin
*/

#ifndef PERLIN_HPP_
#define PERLIN_HPP_

#include "Interface/IMaterial.hpp"
#include "Tools/ConfigNode/ConfigNode.hpp"
#include "Shared/LibraryType.hpp"
#include "Factory/Factory.hpp"

namespace Material {
    class Perlin : public IMaterial {
    public:
        Perlin(const Utils::ConfigNode& node);
        ~Perlin() = default;

        const Utils::Color& shade(
            const Utils::HitRecord& rec,
            const Utils::Ray& ray,
            IMaterial::MaterialProperties& props) const override;

    private:
        Utils::Color _color1;
        Utils::Color _color2;
        float _tileSize;
        mutable Utils::Color _lastColor;
        int p[512];

        float fade(float t) const;
        float lerp(float t, float a, float b) const;
        float grad(int hash, float x, float y, float z) const;
        float noise(float x, float y, float z) const;
    };
}

#endif /* !PERLIN_HPP_ */
