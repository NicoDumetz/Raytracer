#pragma once

#include "Plugins/Primitives/APrimitives.hpp"

namespace Primitive {

    class Triangle : public APrimitive {
    public:
        Triangle(std::shared_ptr<Material::IMaterial> material,
                 math::Point3D a, math::Point3D b, math::Point3D c);

        Triangle(const Utils::ConfigNode& node);

        bool hit(const Utils::Ray& ray, Utils::HitRecord& record) const override;

    private:
        math::Point3D _a, _b, _c;
        math::Vector3D _normal;
    };
}
