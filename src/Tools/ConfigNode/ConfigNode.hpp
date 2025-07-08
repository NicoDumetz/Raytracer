/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <stdexcept>
#include <sstream>
#include <memory>

namespace Utils
{
    class ConfigNode {
    public:
        enum class ConfigType {
            CAMERA,
            SCENE,
            PRIMITIVE,
            LIGHT,
            UNKNOWN
        };
    private:
        ConfigType _type;
        std::string _name;
        std::unordered_map<std::string, std::string> _fields;

    public:
        ConfigNode(ConfigType type, const std::string&) : _type(type) {}

        const std::string& getName() const { return _name; }
        ConfigType getType() const { return _type; }

        bool has(const std::string& key) const;
        const std::string &get(const std::string& key) const;
    };
}
