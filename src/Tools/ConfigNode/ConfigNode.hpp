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
            MATERIAL,
            GLOBAL,
            UNKNOWN
        };

        ConfigNode(ConfigType type, const std::string& name) : _type(type), _name(name) {}

        const std::string& getName() const {return _name;}
        ConfigType getType() const {return _type;}

        bool has(const std::string& key) const;
        const std::string &get(const std::string& key) const;

        const std::unordered_map<std::string, std::string>& getFields() const {return _fields;}
        void setField(const std::string& key, const std::string& value) {_fields[key] = value;}

    private:
        ConfigType _type;
        std::string _name;
        std::unordered_map<std::string, std::string> _fields;
    };
}
