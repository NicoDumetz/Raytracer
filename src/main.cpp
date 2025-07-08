/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/
#include "Core/Core.hpp"
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
        core.run();
    } catch (const std::exception &e) {
        std::cerr << "[Error] " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
