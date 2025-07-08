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
#include "Interface/ILight.hpp"
#include "Tools/ConfigNode/ConfigNode.hpp"

namespace RayTracer
{
    class LightFactory {
        public:
        LightFactory() = default;
        ~LightFactory() = default;

        void addCreator(const std::string& name,
                std::function<std::unique_ptr<ILight>(const ConfigNode&)> creator);

        std::unique_ptr<ILight> create(const ConfigNode& cfg) const;

    private:
        std::unordered_map<std::string,
            std::function<std::unique_ptr<ILight>(const ConfigNode&)>> _registry;
    };
}