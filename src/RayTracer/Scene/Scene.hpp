/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

// Scene.hpp
#pragma once

#include <memory>
#include <vector>
#include "Tools/Math/Matrix/TransformMatrix.hpp"
#include "Interface/IPrimitive.hpp"
#include "Interface/ILight.hpp"
#include "Interface/ICamera.hpp"
#include "Tools/HitRecord/HitRecord.hpp"
#include "Tools/Ray/Ray.hpp"
#include <limits>
#include "Tools/Color/Color.hpp"

namespace RayTracer
{
    enum class AntialiasingType {
        NONE,
        SUPERSAMPLING,
    };

    class Scene {
    private:
        std::vector<std::shared_ptr<Primitive::IPrimitive>> _primitives;
        std::vector<std::shared_ptr<Light::ILight>> _lights;
        std::unique_ptr<Cam::ICamera> _camera;
        Utils::Color _backgroundColor = Utils::Color(0, 0, 0, 1);
        AntialiasingType _antialiasingType = AntialiasingType::NONE;
        int _antialiasingSamples = 1;

    public:
        Scene(std::vector<std::shared_ptr<Primitive::IPrimitive>> primitives = {},
            std::vector<std::shared_ptr<Light::ILight>> lights = {},
            std::unique_ptr<Cam::ICamera> camera = nullptr,
            const Utils::Color& backgroundColor = Utils::Color(0, 0, 0, 1),
            AntialiasingType antialiasingType = AntialiasingType::NONE,
            int antialiasingSamples = 1);

        bool trace(Utils::Ray& ray, Utils::HitRecord& record) const;

        bool hasCamera() const;
        const Cam::ICamera& getCamera() const;

        const std::vector<std::shared_ptr<Primitive::IPrimitive>>& getPrimitives() const;
        const std::vector<std::shared_ptr<Scene>>& getChildren() const;
        const std::vector<std::shared_ptr<Light::ILight>>& getLights() const;
        AntialiasingType getAntialiasingType() const {return _antialiasingType;}
        int getAntialiasingSamples() const {return _antialiasingSamples;}
        void setAntialiasingType(AntialiasingType type) {_antialiasingType = type;}
        void setAntialiasingSamples(int samples) {_antialiasingSamples = samples;}
        void setBackgroundColor(const Utils::Color& color) {_backgroundColor = color;}
        const Utils::Color& getBackgroundColor() const {return _backgroundColor;}
    };
}
