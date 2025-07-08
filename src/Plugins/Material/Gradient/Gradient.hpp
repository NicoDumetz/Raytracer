/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** Gradient
*/

#ifndef GRADIENT_HPP_
#define GRADIENT_HPP_

#include "Interface/IMaterial.hpp"
#include "Tools/ConfigNode/ConfigNode.hpp"
#include "Shared/LibraryType.hpp"
#include "Factory/Factory.hpp"

namespace Material {

class GradientColor : public IMaterial {
public:
    GradientColor(const Utils::ConfigNode& node);
    ~GradientColor() = default;

    const Utils::Color& shade(const Utils::HitRecord& rec,
                              const Utils::Ray& ray,
                              MaterialProperties& props) const override;

private:
    Utils::Color _colorTop;
    Utils::Color _colorBottom;
    mutable Utils::Color _result;
};

}


#endif /* !GRADIENT_HPP_ */
