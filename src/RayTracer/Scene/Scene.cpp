/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Scene.hpp"

bool RayTracer::Scene::hit(const Ray &, HitRecord &) const
{
    return false;
}

const RayTracer::Camera &RayTracer::Scene::getCamera() const
{
    if (!_camera)
        throw std::runtime_error("No camera attached to this scene.");
    return *_camera;
}
