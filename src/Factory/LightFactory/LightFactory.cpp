/*
** EPITECH PROJECT, 2025
** LightFactory.hpp
** File description:
** Project
*/

#include "LightFactory.hpp"

void RayTracer::LightFactory::addCreator(const std::string &name, std::function<std::unique_ptr<ILight>(const ConfigNode &)> creator)
{
    _registry[name] = std::move(creator);
}

std::unique_ptr<RayTracer::ILight> RayTracer::LightFactory::create(
    const ConfigNode &cfg) const
{
    auto it = _registry.find(cfg.getName());
    if (it != _registry.end())
        return it->second(cfg);
    throw std::runtime_error("Light type '"
        + cfg.getName()
        + "' not registered.");
}
