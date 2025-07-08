/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#pragma once
#include <iostream>

namespace Utils
{
    class Color {
    public:
        Color() : r(0), g(0), b(0), a(1) {}
        Color(float red,
            float green,
            float blue,
            float alpha)
        : r(red), g(green), b(blue), a(alpha) {}
        
        float r;
        float g;
        float b;
        float a;
    };
    inline std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << "Color(r=" << color.r
           << ", g=" << color.g
           << ", b=" << color.b
           << ", a=" << color.a << ")";
        return os;
    }
} // namespace Utils

