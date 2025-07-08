/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** LibraryObject.cpp
*/

#include "LibraryObject.hpp"

namespace RayTracer
{
LibraryObject::LibraryObject(const std::string &path) : _path(path)
{
    _handle = dlopen(path.c_str(), RTLD_LAZY);
    if (_handle == nullptr)
        throw std::runtime_error(dlerror());

    auto nameh = reinterpret_cast<const char *(*)()>(dlsym(_handle, "name"));
    if (nameh == nullptr)
        throw std::runtime_error(dlerror());
    _name = nameh();

    auto typeh = reinterpret_cast<RayTracer::Ltype(*)()>(dlsym(_handle, "type"));
    if (typeh == nullptr)
        throw std::runtime_error(dlerror());
    _type = typeh();
    _loaded = true;
};

} // namespace RayTracer
