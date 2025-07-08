#include "Camera.hpp"
/*
** EPITECH PROJECT, 2025
** Cam
** File description:
** main
*/

Cam::Camera::Camera(Resolution res,
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

Cam::Camera::Camera(const Utils::ConfigNode& node)
{
    if (!node.has("width") || !node.has("height") || !node.has("position") || !node.has("target") || !node.has("up") || !node.has("fov"))
        throw std::runtime_error("[Camera] Missing required fields in config node.");
    _resolution = {std::stoi(node.get("width")), std::stoi(node.get("height"))};
    _position = node.parsePoint3D("position");
    _up = node.parseVector3("up");
    _fov = std::stof(node.get("fov"));
    _forward = (node.parsePoint3D("target") - _position).normalized();
    _right = _forward.cross(_up).normalized();
    _up = _right.cross(_forward).normalized();
}


Utils::Ray Cam::Camera::generateRay(int x, int y) const
{
    float aspectRatio = static_cast<float>(_resolution.width) / _resolution.height;
    float scale = std::tan((_fov * 0.5f) * (M_PI / 180.0f));

    float ndcX = (x + 0.5f) / _resolution.width;
    float ndcY = (y + 0.5f) / _resolution.height;

    float screenX = (2 * ndcX - 1) * aspectRatio * scale;
    float screenY = (1 - 2 * ndcY) * scale;

    math::Vector3D direction = 
        (_forward + _right * screenX + _up * screenY).normalized();
    return Utils::Ray(_position, direction);
}

extern "C" {

    void registerPlugin(RayTracer::Factory<Cam::ICamera>& factory)
    {
        factory.addCreator("camera", [](const Utils::ConfigNode& node) {
            return std::make_unique<Cam::Camera>(node);
        });
    }

    RayTracer::Ltype type()
    {
        return RayTracer::Ltype::CAMERA;
    }

    const char* name()
    {
        return "camera";
    }

}