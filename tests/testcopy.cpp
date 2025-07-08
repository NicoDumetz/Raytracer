// DemoScene.cpp
// -----------------------------
// EPITECH PROJECT - RAYTRACER
// Scène démonstrative avec primitives, transformations, et lumières
// -----------------------------

#include "Plugins/Renders/SFML/SFMLRenderer.hpp"
#include "Plugins/Camera/Camera.hpp"
#include "Plugins/Primitives/Sphere/Sphere.hpp"
#include "Plugins/Primitives/Cone/Cone.hpp"
#include "Plugins/Primitives/Cylinder/Cylinder.hpp"
#include "Plugins/Primitives/Plane/Plane.hpp"
#include "Plugins/Material/FlatColor/FlatColor.hpp"
#include "Plugins/Light/DirectionnalLight/DirectionnalLight.hpp"
#include "Plugins/Light/AmbientLight/AmbientLight.hpp"
#include "RayTracer/LightManager/LightManager.hpp"
#include "RayTracer/Scene/Scene.hpp"
#include <iostream>
#include <cmath>

int main() {
    // === CONFIGURATION DE BASE ===
    RayTracer::LightManager lightManager; // Gestionnaire de lumière

    // Création de la caméra
    Cam::Camera::Resolution res{1280, 720}; // Taille de l'image calculée
    math::Point3D cameraPos(0.0f, 0.0f, -500.0f); // Position de la caméra
    math::Point3D target(0.0f, 0.0f, 0.0f); // Point visé par la caméra
    math::Vector3D up(0.0f, 1.0f, 0.0f); // Orientation verticale de la caméra
    float fov = 60.0f; // Champ de vision en degrés

    Utils::Color bgColor(0.05f, 0.05f, 0.1f, 1.0f); // Couleur de fond
    auto cam = std::make_unique<Cam::Camera>(res, cameraPos, target, up, fov); // Instanciation de la caméra

    // === MATÉRIAUX (COULEURS UNIQUES) ===
    auto pinkMat  = std::make_shared<Material::FlatColor>(Utils::Color(1.0f, 0.41f, 0.71f, 1.0f));
    auto blueMat  = std::make_shared<Material::FlatColor>(Utils::Color(0.27f, 0.51f, 0.71f, 1.0f));
    auto greenMat = std::make_shared<Material::FlatColor>(Utils::Color(0.23f, 0.70f, 0.44f, 1.0f));
    auto floorMat = std::make_shared<Material::FlatColor>(Utils::Color(0.9f, 0.2f, 0.4f, 1.0f));
    auto wallMat  = std::make_shared<Material::FlatColor>(Utils::Color(0.2f, 1.0f, 0.5f, 1.0f));
    auto wallBlue = std::make_shared<Material::FlatColor>(Utils::Color(0.3f, 0.3f, 1.0f, 1.0f));

    // === PRIMITIVES ===
    std::vector<std::shared_ptr<Primitive::IPrimitive>> primitives;

    // Sphère avec rotation autour de son centre + translation
    auto sphere1 = std::make_shared<Primitive::Sphere>(pinkMat, math::Point3D(0.0f, 0.0f, 300.0f), 100.0f);
    math::TransformMatrix trans;
    trans.rotateAroundPointY(sphere1->getPosition(), 45.0 * M_PI / 180.0); // Rotation Y autour du centre
    trans.applyTranslation(math::Vector3D(0, 200.0f, 0)); // Translation en Y
    sphere1->applyTransform(trans); // Application
    primitives.push_back(sphere1);

    // Plan incliné via rotation autour de Z
    auto inclinedPlane = std::make_shared<Primitive::Plane>(floorMat, math::Point3D(0.0f, -200.0f, 0.0f), math::Vector3D(0.0f, 1.0f, 0.0f));
    math::TransformMatrix inclineRot;
    inclineRot.rotateAroundPointZ(inclinedPlane->getPosition(), -15.0 * M_PI / 180.0);
    inclinedPlane->applyTransform(inclineRot);
    primitives.push_back(inclinedPlane);

    // Cône inversé par rotation autour de son sommet
    auto cone = std::make_shared<Primitive::Cone>(blueMat, math::Point3D(250.0f, 100.0f, 0.0f), 200, 100);
    math::TransformMatrix t;
    t.rotateAroundAxis(cone->getPosition(), math::Vector3D(1, 0, 0), M_PI); // Rotation X 180°
    cone->applyTransform(t);
    primitives.push_back(cone);

    // Cylindre incliné par rotation X puis translation Y
    auto cylindre = std::make_shared<Primitive::Cylinder>(greenMat, math::Point3D(-250.0f, -50.0f, 250.0f),  200.0f, 70.0f);
    math::TransformMatrix c;
    c.rotateAroundAxis(cylindre->getPosition(), math::Vector3D(1, 0, 0),  45 * M_PI / 180.0);
    c.applyTranslation(math::Vector3D(0, 100.0f, 0));
    cylindre->applyTransform(c);
    primitives.push_back(cylindre);

    // Murs : arrière et gauche
    primitives.push_back(std::make_shared<Primitive::Plane>(wallMat,  math::Point3D(0.0f, 0.0f, 600.0f),  math::Vector3D(0.0f, 0.0f, -1.0f)));
    primitives.push_back(std::make_shared<Primitive::Plane>(wallBlue, math::Point3D(-500.0f, 0.0f, 0.0f), math::Vector3D(1.0f, 0.0f, 0.0f)));

    // === LUMIÈRES ===
    std::vector<std::shared_ptr<Light::ILight>> lights = {
        std::make_shared<Light::DirectionalLight>(math::Vector3D(0.0f, -1.0f, 2.0f), Utils::Color(0.8f, 0.3f, 0.7f, 1.0f)),
        std::make_shared<Light::DirectionalLight>(math::Vector3D(-1.0f, -1.0f, 2.0f), Utils::Color(0.2f, 1.0f, 0.5f, 1.0f)),
        std::make_shared<Light::DirectionalLight>(math::Vector3D(-1.0f, 0.0f, 0.0f), Utils::Color(1.0f, 1.0f, 0.5f, 1.0f)),
        std::make_shared<Light::AmbientLight>(Utils::Color(0.3f, 0.3f, 0.3f, 1.0f))
    };

    // === SCÈNE ===
    RayTracer::Scene scene(primitives, lights, std::move(cam)); // Composition de la scène
    const auto& sceneCam = scene.getCamera(); // Caméra utilisée

    // === RENDU ===
    std::vector<std::vector<Utils::HitRecord>> hitArray(res.height, std::vector<Utils::HitRecord>(res.width));
    for (int y = 0; y < res.height; ++y) {
        for (int x = 0; x < res.width; ++x) {
            Utils::Ray ray = sceneCam.generateRay(x, y); // Génère un rayon pour chaque pixel
            Utils::HitRecord record;
            if (scene.trace(ray, record)) {
                Utils::Color color = lightManager.computeLighting(record, scene, ray); // Lumière appliquée
                record.setColor(color);
                hitArray[y][x] = record;
            } else {
                hitArray[y][x] = Utils::HitRecord(); // Arrière-plan
            }
        }
    }

    // === AFFICHAGE AVEC SFML ===
    Renderer::SFMLRenderer sfml;
    sfml.openWindow(res.width, res.height, bgColor);
    while (sfml.isOpen()) {
        while (sfml.pollEvent()) {} // Gestion des événements
        sfml.clean(); // Efface l'écran
        sfml.drawPixelArray(hitArray); // Affiche les pixels
        sfml.display(); // Met à jour la fenêtre
    }

    return 0;
}
