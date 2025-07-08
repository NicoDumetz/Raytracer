/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** PointLight
*/

#ifndef POINTLIGHT_HPP_
#define POINTLIGHT_HPP_

#include "Interface/ILight.hpp"
#include "RayTracer/Scene/Scene.hpp"
#include "Tools/ConfigNode/ConfigNode.hpp"
#include "Tools/Color/Color.hpp"
#include "Tools/Ray/Ray.hpp"
#include "Shared/LibraryType.hpp"
#include "Factory/Factory.hpp"
#include <memory>

namespace Light {

class PointLight : public ILight {
public:
    PointLight(const math::Point3D& position, const Utils::Color& intensity);
    PointLight(const Utils::ConfigNode& node);

    Utils::Color illuminate(const Utils::HitRecord& hit, const RayTracer::Scene& scene) const override;

private:
    math::Point3D _position;
    Utils::Color _intensity;
};

}


#endif /* !POINTLIGHT_HPP_ */
