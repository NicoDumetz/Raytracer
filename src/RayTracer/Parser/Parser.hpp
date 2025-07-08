// Parser.hpp
#pragma once

#include <vector>
#include <string>
#include "Tools/ConfigNode/ConfigNode.hpp"
#include <libconfig.h++>
#include <iomanip>
#include <functional>


namespace RayTracer {

    class SceneParser {
    public:
        SceneParser(const std::string& filename);
        ~SceneParser() = default;

        const std::vector<Utils::ConfigNode>& getNodes() const {return _nodes;}

    private:
        std::vector<Utils::ConfigNode> _nodes;

        void parseFile(const std::string& filename);
        void parseGlobal(const libconfig::Setting& root);
        void parseCamera(const libconfig::Setting& root);
        void parseMaterials(const libconfig::Setting& root);
        void parsePrimitives(const libconfig::Setting& root);
        void parseLights(const libconfig::Setting& root);

        Utils::ConfigNode parsePrimitive(const libconfig::Setting& prim);
        Utils::ConfigNode parseLight(const libconfig::Setting& light);

        static std::string formatVector(const libconfig::Setting& setting);
        static std::string formatColor(const libconfig::Setting& setting);

        using FieldHandler = std::function<void(Utils::ConfigNode&, const libconfig::Setting&)>;
        const std::unordered_map<std::string, FieldHandler> _primitiveFieldHandlers = {
            {"center", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("center", formatVector(setting));
            }},
            {"point", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("point", formatVector(setting));
            }},
            {"normal", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("normal", formatVector(setting));
            }},
            {"radius", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                float radius = static_cast<float>(static_cast<int>(setting));
                node.setField("radius", std::to_string(radius));
            }},
            {"height", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                float height = static_cast<float>(static_cast<int>(setting));
                node.setField("height", std::to_string(height));
            }},
            {"a", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("a", formatVector(setting));
            }},
            {"b", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("b", formatVector(setting));
            }},
            {"c", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("c", formatVector(setting));
            }},
            {"translate", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("translate", formatVector(setting));
            }},
            {"rotateX", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                float angle = static_cast<float>((double)setting);
                node.setField("rotateX", std::to_string(angle));
            }},
            {"rotateY", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                float angle = static_cast<float>((double)setting);
                node.setField("rotateY", std::to_string(angle));
            }},
            {"rotateZ", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                float angle = static_cast<float>((double)setting);
                node.setField("rotateZ", std::to_string(angle));
            }},
            {"size", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                float size = static_cast<float>((double)setting);
                node.setField("size", std::to_string(size));
            }},
            {"minY", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                float minY = static_cast<float>((double)setting);
                node.setField("minY", std::to_string(minY));
            }},
            {"maxY", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                float maxY = static_cast<float>((double)setting);
                node.setField("maxY", std::to_string(maxY));
            }},
            {"major_radius", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                float R = static_cast<float>((double)setting);
                node.setField("major_radius", std::to_string(R));
            }},
            {"minor_radius", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                float r = static_cast<float>((double)setting);
                node.setField("minor_radius", std::to_string(r));
            }},
        };


        using MaterialHandler = std::function<void(Utils::ConfigNode&, const libconfig::Setting&)>;
        const std::unordered_map<std::string, MaterialHandler> _materialFieldHandlers = {
            {"type", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("type", setting.c_str());
            }},
            {"name", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("name", setting.c_str());
            }},
            {"color", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("color", formatColor(setting));
            }},
            {"color1", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("color1", formatColor(setting));
            }},
            {"color2", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("color2", formatColor(setting));
            }},
            {"tileSize", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                float tileSize = static_cast<float>(setting);
                node.setField("tileSize", std::to_string(tileSize));
            }},
            {"ior", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                float ior = static_cast<float>(setting);
                node.setField("ior", std::to_string(ior));
            }},
            {"colorTop", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("colorTop", formatColor(setting));
            }},
            {"colorBottom", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("colorBottom", formatColor(setting));
            }},
        };

        const std::unordered_map<std::string, FieldHandler> _lightFieldHandlers = {
            {"color", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("color", formatColor(setting));
            }},
            {"direction", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("direction", formatVector(setting));
            }},
            {"position", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("position", formatVector(setting));
            }}
        };
    };
}