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
        std::vector<std::vector<Utils::HitRecord>> hitArray(res.height, std::vector<Utils::HitRecord>(res.width));

        // === TRACER LES RAYONS ===
        for (int y = 0; y < res.height; ++y) {
            for (int x = 0; x < res.width; ++x) {
                Utils::Ray ray = cam.generateRay(x, y);
                Utils::HitRecord record;
                if (scene.trace(ray, record)) {
                    Utils::Color color = lightManager.computeDirectLighting(record, scene);
                    record.setColor(color);
                    hitArray[y][x] = record;
                } else {
                    hitArray[y][x] = Utils::HitRecord();
                }
            }
        }

        // === AFFICHAGE SFML ===
        Renderer::SFMLRenderer sfml;
        sfml.openWindow(res.width, res.height, bgColor);
        while (sfml.isOpen()) {
            while (sfml.pollEvent()) {}
            sfml.clean();
            std::vector<std::vector<Utils::Color>> colorArray(res.height, std::vector<Utils::Color>(res.width));

            for (int y = 0; y < res.height; ++y) {
                for (int x = 0; x < res.width; ++x) {
                    colorArray[y][x] = hitArray[y][x].getColor();
                }
            }

            sfml.drawPixelArray(colorArray);
            sfml.display();
        }

    } catch (const std::exception &e) {
        std::cerr << "[Error] " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
