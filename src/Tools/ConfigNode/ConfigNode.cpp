/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include "ConfigNode.hpp"

bool RayTracer::ConfigNode::has(const std::string &key) const
{
    return _fields.find(key) != _fields.end();
}

const std::string &RayTracer::ConfigNode::get(const std::string &key) const
{
    auto it = _fields.find(key);
    if (it == _fields.end())
        throw std::runtime_error("Field '" + key + "' not found.");
    return it->second;
}