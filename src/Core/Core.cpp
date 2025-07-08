/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include "Core.hpp"

RayTracer::Core::Core(const std::string& filename, char** env)
    : _libLoader(PLUGIN_PATH),
      _parser(std::make_unique<SceneParser>(filename)),
      _primitiveFactory(std::make_shared<Factory<Primitive::IPrimitive>>()),
      _materialFactory(std::make_shared<Factory<Material::IMaterial>>()),
      _lightFactory(std::make_shared<Factory<Light::ILight>>()),
      _cameraFactory(std::make_shared<Factory<Cam::ICamera>>())
{
    checkEnvDisplay(env);
    for (const auto& lib : _libLoader.getAllLibs()) {
        auto type = lib->type();
        auto it = _registry.find(type);
        if (it != _registry.end())
            it->second(*lib);
    }
    _sceneBuilder = std::make_unique<SceneBuilder>(
        _primitiveFactory,
        _lightFactory,
        _materialFactory,
        _cameraFactory,
        _parser->getNodes()
    );
}

void RayTracer::Core::checkEnvDisplay(char **env)
{
    /* ^ start
    ** : first  char
    ** [0-9] one or many num
    ** (.[0-9]+)? option with number after .
    ** $ end
    */
    std::regex displayRegex(R"(^(:[0-9]+(.[0-9]+)?)$)");
    std::string lines;
    bool envDisplay = false;

    for (int i = 0; env[i]; i++) {
        lines = env[i];
        if (lines.rfind("DISPLAY=", 0) == 0 && std::regex_match(lines.substr(8), displayRegex)) {
            envDisplay = true;
            break;
        }
    }
    if (!envDisplay)
        throw std::runtime_error("Error: DISPLAY is missing or invalid. Please run in a graphical environment.");
}
