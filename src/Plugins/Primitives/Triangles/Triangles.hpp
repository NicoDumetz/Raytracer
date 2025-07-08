#pragma once

#include "Plugins/Primitives/APrimitives.hpp"

namespace Primitive {

    class Triangle : public APrimitive {
    public:
        Triangle(std::shared_ptr<Material::IMaterial> material,
                 math::Point3D a, math::Point3D b, math::Point3D c);

        Triangle(const Utils::ConfigNode& node);

        bool hit(const Utils::Ray& ray, Utils::HitRecord& record) const override;

        const Utils::AABB getBoundingBox() const {return calculateBox();};
    private:
        math::Point3D _a, _b, _c;
        math::Vector3D _normal;

        Utils::AABB calculateBox() const
        {
            double minX = std::min({ _a.x, _b.x, _c.x });
            double maxX = std::max({ _a.x, _b.x, _c.x });
            double minY = std::min({ _a.y, _b.y, _c.y });
            double maxY = std::max({ _a.y, _b.y, _c.y });
            double minZ = std::min({ _a.z, _b.z, _c.z });
            double maxZ = std::max({ _a.z, _b.z, _c.z });

            math::Vector3D min(minX, minY, minZ);
            math::Vector3D max(maxX, maxY, maxZ);

            return Utils::AABB(min, max);
        }
    };
}
