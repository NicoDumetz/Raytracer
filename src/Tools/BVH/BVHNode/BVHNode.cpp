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

    if (!left && !right) return nullptr;
    if (!left) return right;
    if (!right) return left;

    Utils::AABB box = AABB::surroundingBox(left->box(), right->box());
    return std::make_shared<BVHNode>(box, nullptr, left, right);
}

bool BVHNode::hit(const Ray &ray, HitRecord &record, float tMin, float tMax) const
{
    if (!_box.intersect(ray, tMin, tMax)) {
        return false;
    }
    bool hitAnything = false;

    if (_primitive) {
        HitRecord tempRecord;
        if (_primitive->hit(ray, tempRecord)) {
            double t = tempRecord.getDistance();
            if (t >= tMin && t < tMax) {
                record = tempRecord;
                hitAnything = true;
            }
    }
    } else {
        float closest = tMax;
        if (_left) {
            HitRecord leftRecord;
            if (_left->hit(ray, leftRecord, tMin, closest)) {
                record = leftRecord;
                closest = record.getDistance();
                hitAnything = true;
            }
        }
        if (_left) {
            HitRecord rightRecord;
            if (_left->hit(ray, rightRecord, tMin, closest)) {
                record = rightRecord;
                closest = record.getDistance();
                hitAnything = true;
            }
        }
    }
    return hitAnything;
}
} // namespace Utils