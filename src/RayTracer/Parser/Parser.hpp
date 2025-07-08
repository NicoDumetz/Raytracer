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
            }}
        };

        const std::unordered_map<std::string, FieldHandler> _lightFieldHandlers = {
            {"color", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("color", formatColor(setting));
            }},
            {"direction", [](Utils::ConfigNode& node, const libconfig::Setting& setting) {
                node.setField("direction", formatVector(setting));
            }}
        };
    };
}