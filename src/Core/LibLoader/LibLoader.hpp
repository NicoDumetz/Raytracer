/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include "LibraryObject.hpp"

namespace RayTracer
{
class LibLoader
{
public:
    LibLoader(const std::string &path);
    ~LibLoader() = default;

    LibraryObject &getLib(const std::string &path, const Raytracer::Ltype &type);
private:
    std::vector<std::unique_ptr<LibraryObject>> _libs = {};
};
} // namespace RayTracer
