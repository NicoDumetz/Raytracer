/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#pragma once

class Color {
public:
    Color() : r(0), g(0), b(0), a(255) {}
    Color(unsigned short red,
        unsigned short green,
        unsigned short blue,
        unsigned short alpha)
    : r(red), g(green), b(blue), a(alpha) {}
    
    unsigned short r;
    unsigned short g;
    unsigned short b;
    unsigned short a;
};