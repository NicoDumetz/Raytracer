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

    auto typeh = reinterpret_cast<Raytracer::Ltype(*)()>(dlsym(_handle, "type"));
    if (typeh == nullptr)
        throw std::runtime_error(dlerror());
    _type = typeh();
    _loaded = true;
};

template<typename T>
std::unique_ptr<T> LibraryObject::get(std::string &symbol)
{
    if (_loaded == false)
        return nullptr;
    auto sym = dlsym(_handle, symbol.c_str());
    if (sym == nullptr)
        throw std::runtime_error(dlerror());
    return reinterpret_cast<T>(sym);
};
} // namespace RayTracer
