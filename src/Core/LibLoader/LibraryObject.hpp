/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** LibraryObject.hpp
*/

#include <dlfcn.h>
#include <stdexcept>
#include <iostream>
#include <memory>
#include "Shared/LibraryType.hpp"

namespace RayTracer
{
class LibraryObject
{
public:
    LibraryObject(const std::string &path);

    ~LibraryObject() {if (_handle) dlclose(_handle);};

    template<typename T>
    std::unique_ptr<T> get(std::string &symbol);

    bool isLoaded() {return _loaded;};
    std::string &path() {return _path;};
    std::string &name() {return _name;};
    Raytracer::Ltype &type() {return _type;};

private:
    bool _loaded = false;
    std::string _path = "";
    std::string _name = "";
    Raytracer::Ltype _type = Raytracer::Ltype::UNKNOWN;
    void *_handle = nullptr;
};
} // namespace RayTracer
