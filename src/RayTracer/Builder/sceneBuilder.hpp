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

        const Scene& getScene() const {return this->_scene;}

    private:
        void buildScene();

        template<typename T>
        void handleGenericVector(const Utils::ConfigNode& node, const std::shared_ptr<Factory<T>>& factory, std::vector<std::shared_ptr<T>>& output);

        template<typename T>
        void handleGenericUnique(const Utils::ConfigNode& node, const std::shared_ptr<Factory<T>>& factory, std::unique_ptr<T>& output);

        void handleMaterial(const Utils::ConfigNode& node);
        void handleGlobalSettings(const Utils::ConfigNode& node);
        AntialiasingType parseAntialiasingType(const std::string& str);


    private:
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

        const std::unordered_map<Utils::ConfigNode::ConfigType, std::function<void(const Utils::ConfigNode&)>> _handlers = {
            {Utils::ConfigNode::ConfigType::MATERIAL, [this](const Utils::ConfigNode& node)
                {this->handleMaterial(node);}},
            {Utils::ConfigNode::ConfigType::PRIMITIVE, [this](const Utils::ConfigNode& node)
                {this->handleGenericVector(node, _primitiveFactory, _primitives);}},
            {Utils::ConfigNode::ConfigType::LIGHT, [this](const Utils::ConfigNode& node)
                {this->handleGenericVector(node, _lightFactory, _lights);}},
            {Utils::ConfigNode::ConfigType::CAMERA, [this](const Utils::ConfigNode& node)
                {this->handleGenericUnique(node, _cameraFactory, _camera);}},
            {Utils::ConfigNode::ConfigType::GLOBAL, [this](const Utils::ConfigNode& node)
                {this->handleGlobalSettings(node);}}
        };

        const std::unordered_map<std::string, AntialiasingType> _antialiasingTypeMap = {
            {"supersampling", AntialiasingType::SUPERSAMPLING}
        };
    };
}