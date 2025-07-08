/*
** EPITECH PROJECT, 2025
** IPrimitive.hpp
** File description:
** Project
*/

#pragma once

#include <vector>
#include <algorithm>
#include "Tools/BVH/AABB/AABB.hpp"
#include "Interface/IPrimitive.hpp"

namespace Utils
{
class BVHNode
{
public:
    BVHNode() = default;
    BVHNode(const AABB &box,
        std::shared_ptr<Primitive::IPrimitive> primitive = nullptr,
        std::shared_ptr<BVHNode> left = nullptr,
        std::shared_ptr<BVHNode> right = nullptr)
        : _box(box), _primitive(primitive), _left(left), _right(right) {};

    static std::shared_ptr<BVHNode> buildBVH(std::vector<std::shared_ptr<Primitive::IPrimitive>> &primitives, int start, int end);

    bool hit(const Ray &ray, HitRecord &record, float tMin, float tMax) const;

    const AABB &box() const {return _box;};
    const BVHNode &left() const {return *_left;};
    const BVHNode &right() const {return *_right;};
    const std::shared_ptr<Primitive::IPrimitive> &primitive() const {return _primitive;};
private:
    AABB _box;
    std::shared_ptr<Primitive::IPrimitive> _primitive;
    std::shared_ptr<BVHNode> _left;
    std::shared_ptr<BVHNode> _right;
};
} // namespace Utils

