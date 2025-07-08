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
    std::unique_ptr<T> get(const std::string& symbol)
    {
        if (!_loaded)
            return nullptr;
        void* sym = dlsym(_handle, symbol.c_str());
        if (!sym)
            throw std::runtime_error(dlerror());
        return std::unique_ptr<T>(reinterpret_cast<T*>(sym));
    }

    bool isLoaded() {return _loaded;};
    std::string &path() {return _path;};
    std::string &name() {return _name;};
    RayTracer::Ltype &type() {return _type;};

private:
    bool _loaded = false;
    std::string _path = "";
    std::string _name = "";
    RayTracer::Ltype _type = RayTracer::Ltype::UNKNOWN;
    void *_handle = nullptr;
};
} // namespace RayTracer
