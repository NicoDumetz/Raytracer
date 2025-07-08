/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include "LibLoader/LibLoader.hpp"
#include "RayTracer/Parser/Parser.hpp"
#include "RayTracer/Builder/sceneBuilder.hpp"
#include "Plugins/Primitives/Sphere/Sphere.hpp"
#include "Plugins/Primitives/Plane/Plane.hpp"
#include "Plugins/Material/FlatColor/FlatColor.hpp"
#include "Plugins/Light/AmbientLight/AmbientLight.hpp"
#include "Plugins/Light/DirectionnalLight/DirectionnalLight.hpp"
#include "Plugins/Camera/Camera.hpp"
#include "Factory/Factory.hpp"
#include <regex>

#define PLUGIN_PATH std::string("./plugins/")
namespace RayTracer
{
    class Core
    {
    public:
        Core(const std::string& filename, char** env);
        ~Core() = default;

        void checkEnvDisplay(char** env);
        const Scene& getScene() const;

    private:
        LibLoader _libLoader;
        std::unique_ptr<SceneParser> _parser;
        std::unique_ptr<SceneBuilder> _sceneBuilder;

        std::shared_ptr<Factory<Primitive::IPrimitive>> _primitiveFactory;
        std::shared_ptr<Factory<Material::IMaterial>> _materialFactory;
        std::shared_ptr<Factory<Light::ILight>> _lightFactory;
        std::shared_ptr<Factory<Cam::ICamera>> _cameraFactory;

        template<typename T>
        void registerFactory(LibraryObject& lib, std::shared_ptr<Factory<T>>& factory)
        {
            using RegFn = void(*)(Factory<T>&);
            auto reg = lib.get<RegFn>("registerPlugin");
            if (!reg)
                throw std::runtime_error("Missing symbol 'registerPlugin' in plugin.");
            (*reg)(*factory);
        }

        const std::unordered_map<RayTracer::Ltype, std::function<void(LibraryObject&)>> _registry = {
            {RayTracer::Ltype::PRIMITIVE, [this](LibraryObject& lib) {
                registerFactory(lib, _primitiveFactory);
            }},
            {RayTracer::Ltype::MATERIAL, [this](LibraryObject& lib) {
                registerFactory(lib, _materialFactory);
            }},
            {RayTracer::Ltype::LIGHT, [this](LibraryObject& lib) {
                registerFactory(lib, _lightFactory);
            }},
            {RayTracer::Ltype::CAMERA, [this](LibraryObject& lib) {
                registerFactory(lib, _cameraFactory);
            }}
        };
    };
}
