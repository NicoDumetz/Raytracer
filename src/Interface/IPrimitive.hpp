/*
** EPITECH PROJECT, 2025
** IPrimitive.hpp
** File description:
** Project
*/


#pragma once

#ifndef IPRIMITIVE_HPP
#define IPRIMITIVE_HPP

#include <memory>
#include "RayTracer/Ray/Ray.hpp"
#include "Tools/HitRecord/HitRecord.hpp"

namespace RayTracer
{
    class IPrimitive {
    public:
        virtual ~IPrimitive() = default;
        virtual bool hit(const Ray& ray, HitRecord& record) const = 0;
    };
    #endif // IPRIMITIVE_HPP
} // namespace Raytracer

