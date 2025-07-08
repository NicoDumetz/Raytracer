/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** sceneBuilder
*/

#include "RayTracer/Builder/sceneBuilder.hpp"


RayTracer::SceneBuilder::SceneBuilder(
    std::shared_ptr<Factory<Primitive::IPrimitive>> primitiveFactory,
    std::shared_ptr<Factory<Light::ILight>> lightFactory,
    std::shared_ptr<Factory<Material::IMaterial>> materialFactory,
    std::shared_ptr<Factory<Cam::ICamera>> cameraFactory,
    const std::vector<Utils::ConfigNode>& nodes
)
    : _primitiveFactory(primitiveFactory),
    _lightFactory(lightFactory),
    _materialFactory(materialFactory),
    _cameraFactory(cameraFactory),
    _nodes(nodes)
{
    _backgroundColor = Utils::Color(0, 0, 0, 1);
    _antialiasingType = AntialiasingType::NONE;
    _antialiasingSamples = 1;
    buildScene();
}

void RayTracer::SceneBuilder::buildScene()
{
    for (const auto& node : _nodes) {
        auto it = _handlers.find(node.getType());
        if (it != _handlers.end()) {
            it->second(node);
        }
    }
    if (!_camera)
        throw std::runtime_error("No camera found while building scene.");
    _scene = Scene(std::move(_primitives), std::move(_lights), std::move(_camera), _backgroundColor, _antialiasingType, _antialiasingSamples);
}

void RayTracer::SceneBuilder::handleMaterial(const Utils::ConfigNode& node)
{
    const std::string& name = node.getName();
    auto material = _materialFactory->create(node);
    _materials[name] = std::move(material);
}

void RayTracer::SceneBuilder::handlePrimitive(const Utils::ConfigNode& node)
{
    Utils::ConfigNode copy = node;

    const std::string& matName = copy.get("material");
    auto it = _materials.find(matName);
    if (it == _materials.end())
        throw std::runtime_error("[SceneBuilder] Material '" + matName + "' not found for primitive '" + copy.getName() + "'.");
    copy.setMaterial(it->second);
    _primitives.push_back(_primitiveFactory->create(copy));
}

void RayTracer::SceneBuilder::handleGlobalSettings(const Utils::ConfigNode& node)
{
    if (node.has("backgroundColor")) {
        const std::string& colorStr = node.get("backgroundColor");
        float r, g, b, a;
        std::sscanf(colorStr.c_str(), "%f,%f,%f,%f", &r, &g, &b, &a);
        Utils::Color bg(r, g, b, a);
        _backgroundColor = bg;
    }

    if (node.has("antialiasing_type")) {
        const std::string& typeStr = node.get("antialiasing_type");
        AntialiasingType aaType = parseAntialiasingType(typeStr);
        _antialiasingType = aaType;
    }

    if (node.has("antialiasing_samples")) {
        const std::string& samplesStr = node.get("antialiasing_samples");
        int samples = std::stoi(samplesStr);
        _antialiasingSamples = samples;
    }
}

RayTracer::AntialiasingType RayTracer::SceneBuilder::parseAntialiasingType(const std::string& str)
{
    auto it = _antialiasingTypeMap.find(str);
    if (it != _antialiasingTypeMap.end())
        return it->second;
    return AntialiasingType::NONE;
}
