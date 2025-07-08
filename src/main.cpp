/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/
#include "Core/Core.hpp"
#include "Plugins/Renders/SFML/SFMLRenderer.hpp"
#include "RayTracer/LightManager/LightManager.hpp"
#include <iostream>

int main(int ac, char **av, char **env)
{
    if (ac != 2) {
        std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
        std::cout << "\tSCENE_FILE: scene configuration" << std::endl;
        return 0;
    }

    try {
        RayTracer::Core core(av[1], env);
        const RayTracer::Scene& scene = core.getScene();
        const auto& cam = scene.getCamera();
        const auto res = cam.getResolution();
        const Utils::Color& bgColor = scene.getBackgroundColor();

        RayTracer::LightManager lightManager;
        std::vector<std::vector<Utils::Color>> pixelArray(res.height, std::vector<Utils::Color>(res.width));

        // === TRACER LES RAYONS ===
        for (int y = 0; y < res.height; ++y) {
            for (int x = 0; x < res.width; ++x) {
                pixelArray[y][x] = lightManager.traceRay(cam.generateRay(x, y), scene, 3);
            }
        }

        // === AFFICHAGE SFML ===
        Renderer::SFMLRenderer sfml;
        sfml.openWindow(res.width, res.height, bgColor);
        while (sfml.isOpen()) {
            while (sfml.pollEvent()) {}
            sfml.clean();
            sfml.drawPixelArray(pixelArray);
            sfml.display();
        }

    } catch (const std::exception &e) {
        std::cerr << "[Error] " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
