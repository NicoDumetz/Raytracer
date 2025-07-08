/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Scene.hpp"

namespace RayTracer
{
    void printIndent(int level) {
    for (int i = 0; i < level; ++i) std::cout << "  ";
}

// Assuming your AABB class has min() and max() returning a vector with x,y,z
void printAABB(const Utils::AABB& box) {
    auto min = box.min();
    auto max = box.max();
    std::cout << "AABB(min: [" << min.x << ", " << min.y << ", " << min.z << "], "
              << "max: [" << max.x << ", " << max.y << ", " << max.z << "])";
}

void printBVH(const std::shared_ptr<Utils::BVHNode>& node, int level = 0) {
    if (!node) {
        printIndent(level);
        std::cout << "(null)" << std::endl;
        return;
    }

    printIndent(level);
    printAABB(node->box());
    if (node->primitive()) {
        std::cout << " [Leaf Node with primitive]" << std::endl;
    } else {
        std::cout << " [Internal Node]" << std::endl;
        printBVH(node->left(), level + 1);
        printBVH(node->right(), level + 1);
    }
}
Scene::Scene(std::vector<std::shared_ptr<Primitive::IPrimitive>> primitives,
             std::vector<std::shared_ptr<Light::ILight>> lights,
             std::unique_ptr<Cam::ICamera> camera,
             const Utils::Color& backgroundColor,
             AntialiasingType antialiasingType,
             int antialiasingSamples)
    : _primitives(std::move(primitives)),
      _lights(std::move(lights)),
      _camera(std::move(camera)),
      _backgroundColor(backgroundColor),
      _antialiasingType(antialiasingType),
      _antialiasingSamples(antialiasingSamples),
      _BVHRoot(Utils::BVHNode::buildBVH(_primitives, 0, _primitives.size()))
{
    // printBVH(_BVHRoot);
}

bool Scene::trace(const Utils::Ray& ray, Utils::HitRecord& record) const
{
    Utils::HitRecord tempRecord;
    bool hitAnything = false;
    double closest = std::numeric_limits<double>::infinity();

    if (_BVHRoot && _BVHRoot->hit(ray, tempRecord, closest)) {
        record = tempRecord;
        hitAnything = true;
    }
    // for (const auto& primitive : _primitives) {
    //     if (primitive->hit(ray, tempRecord)) {
    //         double t = tempRecord.getDistance();
    //         if (t < epsilon || t >= closest)
    //             continue;
    //         closest = t;
    //         record = tempRecord;
    //         hitAnything = true;
    //     }
    // }
    return hitAnything;
}

bool Scene::hasCamera() const {return _camera != nullptr;}

const Cam::ICamera& Scene::getCamera() const {return *_camera;}

const std::vector<std::shared_ptr<Primitive::IPrimitive>>& Scene::getPrimitives() const {return _primitives;}

const std::vector<std::shared_ptr<Light::ILight>>& Scene::getLights() const {return _lights;}

} // namespace RayTracer