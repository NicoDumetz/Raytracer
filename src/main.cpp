/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/
#include "Core/Core.hpp"
#include <iostream>

int main(int ac, char **av, char **env)
{
    std::string configFile;
    std::string ppmFile = "output.ppm";

    try {
        RayTracer::Core::parseArgs(ac, av, configFile, ppmFile);
        RayTracer::Core core(configFile, ppmFile, env);
        core.run();
    } catch (const std::exception &e) {
        std::cerr << "[Error] " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
