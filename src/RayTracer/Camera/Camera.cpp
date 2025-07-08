#include "Camera.hpp"
/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

RayTracer::Camera::Camera(Resolution res,
    const math::Point3D &pos,
    const math::Point3D &lookAt,
    const math::Vector3D &up,
    float fov)
    : _resolution(res),
    _position(pos),
    _fov(fov)
{
    _forward = (lookAt - pos).normalized();
    _right = _forward.cross(up).normalized();
    _up = _right.cross(_forward).normalized();
}

RayTracer::Ray RayTracer::Camera::generateRay(int x, int y) const
{
    float aspectRatio = static_cast<float>(_resolution.width) / _resolution.height;
    float scale = std::tan((_fov * 0.5f) * (M_PI / 180.0f));

    float ndcX = (x + 0.5f) / _resolution.width;
    float ndcY = (y + 0.5f) / _resolution.height;

    float screenX = (2 * ndcX - 1) * aspectRatio * scale;
    float screenY = (1 - 2 * ndcY) * scale;

    math::Vector3D direction = 
        (_forward + _right * screenX + _up * screenY).normalized();
    return Ray(_position, direction);
}
