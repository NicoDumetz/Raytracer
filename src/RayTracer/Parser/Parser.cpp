/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** Parser.cpp
*/

#include "RayTracer/Parser/Parser.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>


RayTracer::SceneParser::SceneParser(const std::string& filename)
{
    parseFile(filename);
}

void RayTracer::SceneParser::parseFile(const std::string& filename)
{
    libconfig::Config config;

    try {
        config.readFile(filename.c_str());
    } catch (const libconfig::FileIOException& e) {
        throw std::runtime_error("File I/O error while reading: " + filename);
    } catch (const libconfig::ParseException& e) {
        throw std::runtime_error("Parse error at " + std::string(e.getFile()) + ":" + std::to_string(e.getLine()) + " - " + e.getError());
    }
    const libconfig::Setting& root = config.getRoot();
    parseGlobal(root);
    parseCamera(root);
    parseMaterials(root);
    parsePrimitives(root);
    parseLights(root);
}

void RayTracer::SceneParser::parseGlobal(const libconfig::Setting& root)
{
    if (!root.exists("global"))
        return;
    Utils::ConfigNode node(Utils::ConfigNode::ConfigType::GLOBAL, "global");
    const libconfig::Setting& global = root["global"];
    if (global.exists("backgroundColor"))
        node.setField("backgroundColor", formatColor(global["backgroundColor"]));
    if (global.exists("antialiasing")) {
        const auto& aa = global["antialiasing"];
        std::string type;
        int samples;
        if (aa.lookupValue("type", type))
            node.setField("antialiasing_type", type);
        if (aa.lookupValue("samples", samples))
            node.setField("antialiasing_samples", std::to_string(samples));
    }
    _nodes.push_back(node);
}

void RayTracer::SceneParser::parseCamera(const libconfig::Setting& root)
{
    if (!root.exists("camera"))
        return;
    Utils::ConfigNode node(Utils::ConfigNode::ConfigType::CAMERA, "camera");
    const auto& cam = root["camera"];
    float fov;

    node.setField("width", std::to_string(cam["resolution"]["width"].operator int()));
    node.setField("height", std::to_string(cam["resolution"]["height"].operator int()));
    node.setField("position", formatVector(cam["position"]));
    node.setField("target", formatVector(cam["target"]));
    node.setField("up", formatVector(cam["up"]));
    cam.lookupValue("fov", fov);
    node.setField("fov", std::to_string(fov));
    _nodes.push_back(node);
}

void RayTracer::SceneParser::parseMaterials(const libconfig::Setting& root)
{
    if (!root.exists("materials"))
        return;
    const auto& materials = root["materials"];

    for (int i = 0; i < materials.getLength(); i++) {
        const auto& mat = materials[i];
        Utils::ConfigNode node(Utils::ConfigNode::ConfigType::MATERIAL, mat["name"]);
        node.setField("type", mat["type"]);
        if (mat.exists("color"))
            node.setField("color", formatColor(mat["color"]));
        if (mat.exists("ior")) {
                float ior;
                mat.lookupValue("ior", ior);  // plus sûr
                node.setField("ior", std::to_string(ior));
            }
        _nodes.push_back(node);
    }
}

void RayTracer::SceneParser::parsePrimitives(const libconfig::Setting& root)
{
    if (!root.exists("primitives"))
        return;
    const auto& primitives = root["primitives"];

    for (int i = 0; i < primitives.getLength(); i++)
        _nodes.push_back(parsePrimitive(primitives[i]));
}

void RayTracer::SceneParser::parseLights(const libconfig::Setting& root)
{
    if (!root.exists("lights"))
        return;
    const auto& lights = root["lights"];

    if (lights.exists("ambient"))
        _nodes.push_back(parseLight(lights["ambient"]));
    if (lights.exists("directional")) {
        const auto& dirLights = lights["directional"];
        for (int i = 0; i < dirLights.getLength(); i++)
            _nodes.push_back(parseLight(dirLights[i]));
    }
}

Utils::ConfigNode RayTracer::SceneParser::parsePrimitive(const libconfig::Setting& prim)
{
    Utils::ConfigNode node(Utils::ConfigNode::ConfigType::PRIMITIVE, prim["type"]);
    node.setField("type", prim["type"]);
    node.setField("material", prim["material"]);

    for (const auto& [fieldName, handler] : _primitiveFieldHandlers) {
        if (prim.exists(fieldName))
            handler(node, prim[fieldName.c_str()]);
    }

    return node;
}

Utils::ConfigNode RayTracer::SceneParser::parseLight(const libconfig::Setting& light)
{
    std::string type = light.exists("direction") ? "directional" : "ambient";
    Utils::ConfigNode node(Utils::ConfigNode::ConfigType::LIGHT, type);

    for (const auto& [fieldName, handler] : _lightFieldHandlers) {
        if (light.exists(fieldName.c_str()))
            handler(node, light[fieldName.c_str()]);
    }

    return node;
}

std::string RayTracer::SceneParser::formatColor(const libconfig::Setting& color)
{
    int r, g, b, a;
    std::ostringstream oss;

    color.lookupValue("r", r);
    color.lookupValue("g", g);
    color.lookupValue("b", b);
    color.lookupValue("a", a);
    oss << std::fixed << std::setprecision(6) << (r / 255.0f) << "," << (g / 255.0f) << "," << (b / 255.0f) << "," << (a / 255.0f);
    return oss.str();
}

std::string RayTracer::SceneParser::formatVector(const libconfig::Setting& vec)
{
    int x, y, z;
    std::ostringstream oss;

    vec.lookupValue("x", x);
    vec.lookupValue("y", y);
    vec.lookupValue("z", z);
    oss << std::fixed << std::setprecision(6) << static_cast<float>(x) << "," << static_cast<float>(y) << "," << static_cast<float>(z);
    return oss.str();
}
