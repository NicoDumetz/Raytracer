/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#pragma once

#pragma once

#include <vector>
#include <memory>
#include <stdexcept>
#include "Interface/IPrimitive.hpp"
#include "Interface/ILight.hpp"
#include "RayTracer/Camera/Camera.hpp"
#include "RayTracer/Ray/Ray.hpp"
#include "Tools/HitRecord/HitRecord.hpp"

namespace RayTracer {

    class Scene : public IPrimitive {
    private:
        std::unique_ptr<Camera> _camera;
        std::shared_ptr<Scene> _parent;
        std::vector<std::unique_ptr<IPrimitive>> _primitives;
        std::vector<std::unique_ptr<ILight>> _lights;

    public:
        Scene(std::vector<std::unique_ptr<IPrimitive>>&& primitives,
              std::vector<std::unique_ptr<ILight>>&& lights,
              std::unique_ptr<Camera> camera = nullptr,
              std::shared_ptr<Scene> parent = nullptr)
            : _camera(std::move(camera)),
              _parent(std::move(parent)),
              _primitives(std::move(primitives)),
              _lights(std::move(lights)) {}

        bool hit(const Ray& ray, HitRecord& record) const;
        bool hasCamera() const { return _camera != nullptr; }
        const Camera& getCamera() const;
    };
}
