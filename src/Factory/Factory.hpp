/*
** EPITECH PROJECT, 2025
** LightFactory.hpp
** File description:
** Project
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include "Tools/ConfigNode/ConfigNode.hpp"

namespace RayTracer
{
    template <typename T>
    class Factory {
        public:
        Factory() = default;
        ~Factory() = default;

        void addCreator(const std::string& name,
                std::function<std::unique_ptr<T>(const Utils::ConfigNode&)> creator)
        {
            _registry[name] = std::move(creator);
        }

        std::unique_ptr<T> create(const Utils::ConfigNode& cfg) const {
            auto type = cfg.get("type");
            std::cout << "Creating object of type: " << type << std::endl;
            auto it = _registry.find(type);
            if (it != _registry.end())
                return it->second(cfg);
            throw std::runtime_error("Factory error : type '" + type + "' not registered.");
        }

    private:
        std::unordered_map<std::string,
            std::function<std::unique_ptr<T>(const Utils::ConfigNode&)>> _registry;
    };
}