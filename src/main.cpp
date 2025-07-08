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

    if (RayTracer::Core::parseArgs(ac, av, configFile, ppmFile)) {
        std::cout << "USAGE: ./raytracer <SCENE_FILE> [OPTIONS]" << std::endl;
        std::cout << "\tSCENE_FILE: scene configuration" << std::endl;
        std::cout << "\t-o <FILE>: output file name (default: output.ppm)" << std::endl;
        return 84;
    }
    try {
        RayTracer::Core core(configFile, ppmFile, env);
        core.run();
    } catch (const std::exception &e) {
        std::cerr << "[Error] " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
