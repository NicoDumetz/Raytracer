/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include "LibLoader/LibLoader.hpp"
#include "RayTracer/Parser/Parser.hpp"
#include "RayTracer/Builder/sceneBuilder.hpp"
#include "Interface/IPrimitive.hpp"
#include "Interface/ILight.hpp"
#include "Interface/IMaterial.hpp"
#include "Interface/IPrimitive.hpp"
#include "Interface/IRenderer.hpp"
#include "Factory/Factory.hpp"
#include "RayTracer/LightManager/LightManager.hpp"
#include <regex>
#include <string>
#include <thread>

#define PLUGIN_PATH std::string("./plugins/")

namespace RayTracer
{
    class Core
    {
    public:
        Core(const std::string& filename, const std::string& ppmFilename, char** env);
        ~Core() = default;

        static void parseArgs(int argc, char **argv, std::string& configFile, std::string& ppmFile);
        void checkEnvDisplay(char** env);
        const Scene& getScene() const { return _sceneBuilder->getScene();};
        void run();

    private:
        LibLoader _libLoader;
        std::unique_ptr<SceneParser> _parser;
        std::unique_ptr<SceneBuilder> _sceneBuilder;
        const std::string& _ppmFilename;

        std::shared_ptr<Factory<Primitive::IPrimitive>> _primitiveFactory;
        std::shared_ptr<Factory<Material::IMaterial>> _materialFactory;
        std::shared_ptr<Factory<Light::ILight>> _lightFactory;
        std::shared_ptr<Factory<Cam::ICamera>> _cameraFactory;

        std::unique_ptr<Renderer::IRenderer> _render;
        RayTracer::LightManager lightManager;

        template<typename T>
        void registerFactory(LibraryObject& lib, std::shared_ptr<Factory<T>>& factory)
        {
            auto reg = lib.get<void(*)(Factory<T>&)>("registerPlugin");
            if (!reg)
                throw std::runtime_error("Missing symbol 'registerPlugin'");
            reg(*factory);
        }

        template <typename T>
        std::unique_ptr<T> getInstance(LibraryObject &lib) const
        {
            auto *func = lib.get<void *(*)()>("entryPoint");
            if (!func)
                throw std::runtime_error("Missing symbol 'entryPoint'");
            auto *instance = reinterpret_cast<T *>(func());
            if (!instance)
                throw std::runtime_error("Failed to create instance");
            return std::unique_ptr<T>(instance);
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
            }},
            {RayTracer::Ltype::GRAPHIC, [this](LibraryObject& lib) {
                this->_render = getInstance<Renderer::IRenderer>(lib);
            }}
        };
        void writePPM(const std::vector<std::vector<Utils::Color>> &pixelsArray) const;
        static std::string helpMessage();
    };
}
