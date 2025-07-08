/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include "LibLoader/LibLoader.hpp"

#define PLUGIN_PATH std::string("./plugin/")

namespace RayTracer
{
class Core
{
public:
    Core();
    ~Core() = default;

private:
    LibLoader _libLoader;
};
} // namespace RayTracer
