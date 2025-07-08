/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** sceneBuilder
*/
#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include "Tools/ConfigNode/ConfigNode.hpp"
#include "RayTracer/Parser/Parser.hpp"
#include "RayTracer/Scene/Scene.hpp"
#include "Factory/Factory.hpp"
#include "Interface/IPrimitive.hpp"
#include "Interface/ILight.hpp"
#include "Interface/IMaterial.hpp"
#include "Interface/ICamera.hpp"

namespace RayTracer
{
    class SceneBuilder {
    public:
        SceneBuilder(
            std::shared_ptr<Factory<Primitive::IPrimitive>> primitiveFactory,
            std::shared_ptr<Factory<Light::ILight>> lightFactory,
            std::shared_ptr<Factory<Material::IMaterial>> materialFactory,
            std::shared_ptr<Factory<Cam::ICamera>> cameraFactory,
            const std::vector<Utils::ConfigNode>& nodes
        );

        const Scene& getScene() const { return _scene; }

    private:
        void buildScene();
        void handleMaterial(const Utils::ConfigNode& node);
        void handleGlobalSettings(const Utils::ConfigNode& node);
        void handlePrimitive(const Utils::ConfigNode& node);
        AntialiasingType parseAntialiasingType(const std::string& str);

        template<typename T>
        void handleGenericUnique(const Utils::ConfigNode& node, const std::shared_ptr<Factory<T>>& factory, std::unique_ptr<T>& output)
        {
            Utils::ConfigNode copy = node;
            if (!copy.has("type"))
                copy.setField("type", copy.getName());
            output = factory->create(copy);
        }

        template<typename T>
        void handleGenericVector(const Utils::ConfigNode& node, const std::shared_ptr<Factory<T>>& factory, std::vector<std::shared_ptr<T>>& output)
        {
            Utils::ConfigNode copy = node;
            if (!copy.has("type"))
                copy.setField("type", copy.getName());
            output.push_back(factory->create(copy));
        }

        std::shared_ptr<Factory<Primitive::IPrimitive>> _primitiveFactory;
        std::shared_ptr<Factory<Light::ILight>> _lightFactory;
        std::shared_ptr<Factory<Material::IMaterial>> _materialFactory;
        std::shared_ptr<Factory<Cam::ICamera>> _cameraFactory;

        std::vector<Utils::ConfigNode> _nodes;
        RayTracer::Scene _scene;

        std::vector<std::shared_ptr<Primitive::IPrimitive>> _primitives;
        std::vector<std::shared_ptr<Light::ILight>> _lights;
        std::unordered_map<std::string, std::shared_ptr<Material::IMaterial>> _materials;
        std::unique_ptr<Cam::ICamera> _camera;
        Utils::Color _backgroundColor;
        AntialiasingType _antialiasingType;
        int _antialiasingSamples;

        const std::unordered_map<Utils::ConfigNode::ConfigType, std::function<void(const Utils::ConfigNode&)>> _handlers = {
            {Utils::ConfigNode::ConfigType::MATERIAL, [this](const Utils::ConfigNode& node) {
                handleMaterial(node); }},
            {Utils::ConfigNode::ConfigType::PRIMITIVE, [this](const Utils::ConfigNode& node) {
                handlePrimitive(node); }},
            {Utils::ConfigNode::ConfigType::LIGHT, [this](const Utils::ConfigNode& node) {
                handleGenericVector(node, _lightFactory, _lights); }},
            {Utils::ConfigNode::ConfigType::CAMERA, [this](const Utils::ConfigNode& node) {
                handleGenericUnique(node, _cameraFactory, _camera); }},
            {Utils::ConfigNode::ConfigType::GLOBAL, [this](const Utils::ConfigNode& node) {
                handleGlobalSettings(node); }}
        };

        const std::unordered_map<std::string, AntialiasingType> _antialiasingTypeMap = {
            {"supersampling", AntialiasingType::SUPERSAMPLING}
        };
    };
}
