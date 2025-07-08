/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-maximilien.dheripre
** File description:
** Perlin
*/
#include "Perlin.hpp"
#include <cmath>
#include <cstdlib>
#include <random>
#include <numeric>
#include <vector>

namespace Material {

Perlin::Perlin(const Utils::ConfigNode& node)
    : _color1(Utils::Color(1.0f, 1.0f, 1.0f, 1.0f)),
      _color2(Utils::Color(0.0f, 0.0f, 0.0f, 1.0f)),
      _tileSize(1.0f)
{
    unsigned int seed = 1234;
    std::vector<int> perm(256);

    if (node.has("color1"))
        _color1 = node.parseColor("color1");
    if (node.has("color2"))
        _color2 = node.parseColor("color2");
    if (node.has("tileSize"))
        _tileSize = std::stof(node.get("tileSize"));
    std::iota(perm.begin(), perm.end(), 0);
    std::mt19937 rng(seed);
    std::shuffle(perm.begin(), perm.end(), rng);
    for (int i = 0; i < 256; ++i) {
        p[i] = perm[i];
        p[256 + i] = perm[i];
    }
}

float Perlin::fade(float t) const {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float Perlin::lerp(float t, float a, float b) const {
    return a + t * (b - a);
}

float Perlin::grad(int hash, float x, float y, float z) const {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : ((h == 12 || h == 14) ? x : z);
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

float Perlin::noise(float x, float y, float z) const {
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;
    int Z = static_cast<int>(std::floor(z)) & 255;
    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);
    float u = fade(x);
    float v = fade(y);
    float w = fade(z);
    int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
    int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;
    return lerp(w,
        lerp(v,
            lerp(u, grad(p[AA], x, y, z),
                     grad(p[BA], x - 1, y, z)),
            lerp(u, grad(p[AB], x, y - 1, z),
                     grad(p[BB], x - 1, y - 1, z))),
        lerp(v,
            lerp(u, grad(p[AA + 1], x, y, z - 1),
                     grad(p[BA + 1], x - 1, y, z - 1)),
            lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                     grad(p[BB + 1], x - 1, y - 1, z - 1)))
    );
}

const Utils::Color& Perlin::shade(
    const Utils::HitRecord& rec,
    const Utils::Ray&,
    IMaterial::MaterialProperties&) const
{
    const auto& pnt = rec.getPosition();
    float scale = 1.0f / _tileSize;
    float n = noise(pnt.x * scale, pnt.y * scale, pnt.z * scale);
    n = (n + 1.0f) / 2.0f;

    _lastColor = _color1 * n + _color2 * (1.0f - n);
    return _lastColor;
}

} // namespace Material

extern "C" {

void registerPlugin(RayTracer::Factory<Material::IMaterial>& factory)
{
    factory.addCreator("perlin", [](const Utils::ConfigNode& node) {
        return std::make_unique<Material::Perlin>(node);
    });
}

RayTracer::Ltype type()
{
    return RayTracer::Ltype::MATERIAL;
}

const char* name()
{
    return "perlin";
}

}
