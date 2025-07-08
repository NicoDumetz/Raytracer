/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include "LibLoader.hpp"

namespace RayTracer
{
LibLoader::LibLoader(const std::string &path)
{
    if (std::filesystem::exists(path) == false)
            return;
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() != ".so")
            continue;
        auto obj = std::make_unique<LibraryObject>(entry.path().string());
        if (obj->isLoaded())
            _libs.push_back(std::move(obj));
    }
}

LibraryObject &LibLoader::getLib(const std::string &nameLib, const RayTracer::Ltype &type)
{
    for (auto &lib : _libs) {
        if (lib->path() == nameLib && lib->type() == type)
            return *lib;
    }
    throw std::runtime_error("Cannot find library.");
};
} // namespace RayTracer
