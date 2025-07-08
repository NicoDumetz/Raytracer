#pragma once


#include "Interface/IMaterial.hpp"
#include "Tools/ConfigNode/ConfigNode.hpp"
#include "Shared/LibraryType.hpp"
#include "Factory/Factory.hpp"
#include "Tools/Color/Color.hpp"

namespace Material {

    class Checkerboard : public IMaterial {
    public:
        Checkerboard(const Utils::ConfigNode& node);
        ~Checkerboard() = default;

        const Utils::Color& shade(
            const Utils::HitRecord &rec,
            const Utils::Ray &ray,
            IMaterial::MaterialProperties& props) const override;

    private:
        Utils::Color _color1;
        Utils::Color _color2;
        float _tileSize;
        mutable Utils::Color _lastColor;
    };
}
