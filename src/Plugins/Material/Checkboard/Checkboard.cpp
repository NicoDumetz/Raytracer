#include "Checkboard.hpp"
#include <cmath>

namespace Material {

Checkerboard::Checkerboard(const Utils::ConfigNode& node)
{
    _color1 = Utils::Color(1.0f, 1.0f, 1.0f, 1.0f);
    _color2 = Utils::Color(0.0f, 0.0f, 0.0f, 1.0f);
    _tileSize = 100.0f;

    if (node.has("color1"))
        _color1 = node.parseColor("color1");
    if (node.has("color2"))
        _color2 = node.parseColor("color2");
    if (node.has("tileSize"))
        _tileSize = std::stof(node.get("tileSize"));
}

const Utils::Color& Checkerboard::shade(
    const Utils::HitRecord& rec,
    const Utils::Ray&,
    IMaterial::MaterialProperties&) const
{
    const math::Point3D& p = rec.getPosition();
    constexpr float epsilon = 1e-4f;
    float px = std::abs(p.x) < epsilon ? 0.f : p.x;
    float py = std::abs(p.y) < epsilon ? 0.f : p.y;
    float pz = std::abs(p.z) < epsilon ? 0.f : p.z;
    int ix = static_cast<int>(std::floor((px + epsilon) / _tileSize));
    int iy = static_cast<int>(std::floor((py + epsilon) / _tileSize));
    int iz = static_cast<int>(std::floor((pz + epsilon) / _tileSize));
    int sum = ix + iy + iz;
    bool isEven = (sum % 2 == 0);
    _lastColor = isEven ? _color1 : _color2;
    return _lastColor;
}

} // namespace Material

extern "C" {

void registerPlugin(RayTracer::Factory<Material::IMaterial>& factory)
{
    factory.addCreator("checkerboard", [](const Utils::ConfigNode& node) {
        return std::make_unique<Material::Checkerboard>(node);
    });
}

RayTracer::Ltype type()
{
    return RayTracer::Ltype::MATERIAL;
}

const char* name()
{
    return "checkerboard";
}

}
