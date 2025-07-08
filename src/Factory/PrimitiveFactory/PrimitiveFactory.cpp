/*
** EPITECH PROJECT, 2025
** PrimitiveFactory.hpp
** File description:
** Project
*/

#include "PrimitiveFactory.hpp"

void RayTracer::PrimitiveFactory::addCreator(const std::string &name, std::function<std::unique_ptr<IPrimitive>(const ConfigNode &)> creator)
{
    _registry[name] = std::move(creator);
}

std::unique_ptr<RayTracer::IPrimitive> RayTracer::PrimitiveFactory::create(
    const ConfigNode &cfg) const
{
    auto it = _registry.find(cfg.getName());
    if (it != _registry.end())
        return it->second(cfg);
    throw std::runtime_error("Primitive type '"
        + cfg.getName() 
        + "' not registered.");
}
