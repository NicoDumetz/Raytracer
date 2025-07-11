/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Scene.hpp"

namespace RayTracer
{
Scene::Scene(std::vector<std::shared_ptr<Primitive::IPrimitive>> primitives,
             std::vector<std::shared_ptr<Light::ILight>> lights,
             std::unique_ptr<Cam::ICamera> camera,
             const Utils::Color& backgroundColor,
             AntialiasingType antialiasingType,
             int antialiasingSamples)
    : _primitives(std::move(primitives)),
      _lights(std::move(lights)),
      _camera(std::move(camera)),
      _backgroundColor(backgroundColor),
      _antialiasingType(antialiasingType),
      _antialiasingSamples(antialiasingSamples),
      _BVHRoot(Utils::BVHNode::buildBVH(_primitives, 0, _primitives.size())) {}

bool Scene::trace(const Utils::Ray& ray, Utils::HitRecord& record) const
{
    Utils::HitRecord tempRecord;
    bool hitAnything = false;
    double closest = std::numeric_limits<double>::infinity();

    if (_BVHRoot) {
        if (_BVHRoot->hit(ray, tempRecord, closest)) {
            record = tempRecord;
            hitAnything = true;
        }
    }
    return hitAnything;
}

bool Scene::hasCamera() const {return _camera != nullptr;}

const Cam::ICamera& Scene::getCamera() const {return *_camera;}

const std::vector<std::shared_ptr<Primitive::IPrimitive>>& Scene::getPrimitives() const {return _primitives;}

const std::vector<std::shared_ptr<Light::ILight>>& Scene::getLights() const {return _lights;}

} // namespace RayTracer