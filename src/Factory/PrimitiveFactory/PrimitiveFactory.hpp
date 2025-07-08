/*
** EPITECH PROJECT, 2025
** PrimitiveFactory.hpp
** File description:
** Project
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include "Interface/IPrimitive.hpp"
#include "Tools/ConfigNode/ConfigNode.hpp"

namespace RayTracer
{
    class PrimitiveFactory {
        public:
        PrimitiveFactory() = default;
        ~PrimitiveFactory() = default;

        void addCreator(const std::string& name,
                std::function<std::unique_ptr<IPrimitive>(const ConfigNode&)> creator);
        std::unique_ptr<IPrimitive> create(const ConfigNode& cfg) const;
    private:
        std::unordered_map<std::string,
            std::function<std::unique_ptr<IPrimitive>(const ConfigNode&)>> _registry;
    };
}
