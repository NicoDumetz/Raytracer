/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include "ConfigNode.hpp"

bool Utils::ConfigNode::has(const std::string &key) const
{
    return _fields.find(key) != _fields.end();
}

const std::string &Utils::ConfigNode::get(const std::string &key) const
{
    auto it = _fields.find(key);
    if (it == _fields.end())
        throw std::runtime_error("Field '" + key + "' not found.");
    return it->second;
}

Utils::Color Utils::ConfigNode::parseColor(const std::string& field) const
{
    float r, g, b, a;
    std::sscanf(get(field).c_str(), "%f,%f,%f,%f", &r, &g, &b, &a);
    return Color(r, g, b, a);
}

math::Vector3D Utils::ConfigNode::parseVector3(const std::string& field) const
{
    float x, y, z;
    std::sscanf(get(field).c_str(), "%f,%f,%f", &x, &y, &z);
    return math::Vector3D(x, y, z);
}

math::Point3D Utils::ConfigNode::parsePoint3D(const std::string& field) const
{
    float x, y, z;
    std::sscanf(get(field).c_str(), "%f,%f,%f", &x, &y, &z);
    return math::Point3D(x, y, z);
}

float Utils::ConfigNode::parseFloat(const std::string& field) const
{
    float value;
    std::istringstream(get(field)) >> value;
    return value;
}

int Utils::ConfigNode::parseInt(const std::string& field) const
{
    int value;
    std::istringstream(get(field)) >> value;
    return value;
}