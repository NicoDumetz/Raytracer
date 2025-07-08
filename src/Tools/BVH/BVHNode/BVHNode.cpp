/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include "BVHNode.hpp"

namespace Utils
{
std::shared_ptr<BVHNode> BVHNode::buildBVH(std::vector<std::shared_ptr<Primitive::IPrimitive>> &primitives, int start, int end)
{
    if (end <= start)
        return nullptr;

    if ((end - start) == 1) {
        auto primitive = primitives[start];
        return std::make_shared<BVHNode>(primitive->getBoundingBox(), primitive, nullptr, nullptr);
    }

    auto compare = [](const std::shared_ptr<Primitive::IPrimitive> &a,
                        const std::shared_ptr<Primitive::IPrimitive> &b) {
        return a->getBoundingBox().min().x < b->getBoundingBox().min().x;
    };
    std::sort(primitives.begin() + start, primitives.begin() + end, compare);

    int mid = (start + end) / 2;
    auto left = buildBVH(primitives, start, mid);
    auto right = buildBVH(primitives, mid, end);

    if (!left) return right;
    if (!right) return left;

    Utils::AABB box = AABB::surroundingBox(left->box(), right->box());
    return std::make_shared<BVHNode>(box, nullptr, left, right);
}

bool Utils::BVHNode::hit(const Ray &ray, HitRecord &record, double tMax) const
{
    if (!_box.intersect(ray, tMax))
        return false;

    if (_primitive != nullptr) {
        return _primitive->hit(ray, record);
    }
    if (!_left && !_right)
        return false;

    bool hitLeft = false;
    bool hitRight = false;
    HitRecord leftRecord, rightRecord;
    double closestSoFar = tMax;

    if (_left) {
        hitLeft = _left->hit(ray, leftRecord, closestSoFar);
        if (hitLeft)
            closestSoFar = leftRecord.getDistance();
    }

    if (_right) {
        hitRight = _right->hit(ray, rightRecord, closestSoFar);
        if (hitRight)
            closestSoFar = rightRecord.getDistance();
    }

    if (hitLeft && (!hitRight || leftRecord.getDistance() < rightRecord.getDistance())) {
        record = leftRecord;
        return true;
    } else if (hitRight) {
        record = rightRecord;
        return true;
    }

    return false;
}
} // namespace Utils