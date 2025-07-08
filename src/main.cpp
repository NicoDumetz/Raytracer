/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include <exception>
#include <iostream>
#include "Core/Core.hpp"

int main(int ac, char **av, char **env)
{
    (void)av;
    if (ac != 2) {
        std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
        std::cout << "\tSCENE_FILE: scene configuration" << std::endl;
        return 0;
    }
    try {
        RayTracer::Core core(av[1], env);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
        return 0;
}
