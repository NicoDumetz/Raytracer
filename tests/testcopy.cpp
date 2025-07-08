#include "Plugins/Renders/SFML/SFMLRenderer.hpp"
#include "Plugins/Camera/Camera.hpp"
#include "Plugins/Primitives/Sphere/Sphere.hpp"
#include "Plugins/Material/FlatColor/FlatColor.hpp"
#include "Plugins/Light/DirectionnalLight/DirectionnalLight.hpp"
#include "Plugins/Primitives/Plane/Plane.hpp"
#include "Plugins/Light/AmbientLight/AmbientLight.hpp"
#include "RayTracer/LightManager/LightManager.hpp"
#include "RayTracer/Scene/Scene.hpp"
#include <iostream>
#include <cmath>

int main() {
    // === CONFIGURATION DE BASE ===
    RayTracer::LightManager lightManager;
    //Resolution de la caméra != de la taille de la fenetre SFML (doit etre quand meme proportionnel a la taille de la fenetre sinon l'image est deformé)
    Cam::Camera::Resolution res{1280, 720};
    //Position de la caméra ici on est en recul sur la scene le z est negatif
    math::Point3D cameraPos(0.0f, 0.0f, -500.0f);
    //Endroit ou la camera est pointé
    math::Point3D target(0.0f, 0.0f, 0.0f);
    //Axe de la caméra ici la caméra est parallèle avec y le haut de la camera est +y
    math::Vector3D up(0.0f, 1.0f, 0.0f);
    //Champ de vision
    float fov = 60.0f;

    Utils::Color bgColor(0.05f, 0.05f, 0.05f, 1.0f);
    auto cam = std::make_unique<Cam::Camera>(res, cameraPos, target, up, fov);

    // === MATÉRIAUX ===
    auto pinkMat  = std::make_shared<Material::FlatColor>(Utils::Color(1.0f, 0.41f, 0.71f, 1.0f));
    auto blueMat  = std::make_shared<Material::FlatColor>(Utils::Color(0.27f, 0.51f, 0.71f, 1.0f));
    auto greenMat = std::make_shared<Material::FlatColor>(Utils::Color(0.23f, 0.70f, 0.44f, 1.0f));
    auto floorMat = std::make_shared<Material::FlatColor>(Utils::Color(0.9f, 0.2f, 0.4f, 1.0f));
    auto wallMat  = std::make_shared<Material::FlatColor>(Utils::Color(0.2f, 1.0f, 0.5f, 1.0f));
    auto wallBlue = std::make_shared<Material::FlatColor>(Utils::Color(0.3f, 0.3f, 1.0f, 1.0f));

    // === PRIMITIVES ===
    std::vector<std::shared_ptr<Primitive::IPrimitive>> primitives;

    // Sphère transformée par rotation autour de son centre
    auto sphere1 = std::make_shared<Primitive::Sphere>(pinkMat, math::Point3D(0.0f, 0.0f, 300.0f), 100.0f);
    //Creation d'une matrice de transformation (le constructeur l'initialise a identité)
    math::TransformMatrix trans;
    //Rotation autour du centre de la primitive (c'est un cercle donc pas de rendu visuel mais crois moi ca tourne)
    //Et si tu te demande oui on est obligé de passer le point
    trans.rotateAroundPointY(sphere1->getPosition(), 45.0 * M_PI / 180.0);
    //On fais une translation +200 sur l'axe y
    trans.applyTranslation(math::Vector3D(0, 200.0f, 0));
    //Une fois que la matrix est creer avec toute les transformations on l'applique a la primitive;
    sphere1->applyTransform(trans);
    primitives.push_back(sphere1);

    // Plan incliné autour de son point d'origine
    auto inclinedPlane = std::make_shared<Primitive::Plane>(floorMat, math::Point3D(0.0f, -200.0f, 0.0f), math::Vector3D(0.0f, 1.0f, 0.0f));
    math::TransformMatrix inclineRot;
    //Meme principe, ici on tourne autour de l'axe Z
    inclineRot.rotateAroundPointZ(inclinedPlane->getPosition(), -15.0 * M_PI / 180.0);
    inclinedPlane->applyTransform(inclineRot);
    primitives.push_back(inclinedPlane);

    // Autres sphères statiques
    primitives.push_back(std::make_shared<Primitive::Sphere>(greenMat, math::Point3D(-250.0f, -50.0f, 250.0f),  80.0f));
    primitives.push_back(std::make_shared<Primitive::Sphere>(blueMat,  math::Point3D( 250.0f,  50.0f, 300.0f),  80.0f));

    // Sol et murs
    //Un plan prend deux parametre un point par lequel le plan passe et sert de position, et une direction, ici Vector(0, 0, -1) regarde vers nous
    primitives.push_back(std::make_shared<Primitive::Plane>(wallMat,  math::Point3D(0.0f, 0.0f, 600.0f),  math::Vector3D(0.0f, 0.0f, -1.0f)));
    primitives.push_back(std::make_shared<Primitive::Plane>(wallBlue, math::Point3D(-500.0f, 0.0f, 0.0f), math::Vector3D(1.0f, 0.0f, 0.0f)));

    // === LUMIÈRES ===
    //Petit conseil pour la lumiere éviter les couleur avec des valeur a 0 (et toujours utiliser .f)
    //Par exemple prim(Color(0, 0, 1)) et light(Color(1, 1, 0)) donnera l'impression qu'il n'y a pas de lumiere et c'est normal
    std::vector<std::shared_ptr<Light::ILight>> lights = {
        //Pour la direction de la lumiere on donne un vector ici (0, -1, 2) va vers y bas, z devant
        std::make_shared<Light::DirectionalLight>(math::Vector3D(0.0f, -1.0f, 2.0f), Utils::Color(0.8f, 0.3f, 0.7f, 1.0f)),
        std::make_shared<Light::DirectionalLight>(math::Vector3D(-1.0f, -1.0f, 2.0f), Utils::Color(0.2f, 1.0f, 0.5f, 1.0f)),
        std::make_shared<Light::DirectionalLight>(math::Vector3D(-1.0f, 0.0f, 0.0f), Utils::Color(1.0f, 1.0f, 0.5f, 1.0f)),
        std::make_shared<Light::AmbientLight>(Utils::Color(0.3f, 0.3f, 0.3f, 1.0f))
    };

    // === SCÈNE ===
    RayTracer::Scene scene(primitives, lights, std::move(cam));
    const auto& sceneCam = scene.getCamera();

    // === RENDU ===
    std::vector<std::vector<Utils::HitRecord>> hitArray(res.height, std::vector<Utils::HitRecord>(res.width));
    for (int y = 0; y < res.height; ++y) {
        for (int x = 0; x < res.width; ++x) {
            Utils::Ray ray = sceneCam.generateRay(x, y);
            Utils::HitRecord record;
            if (scene.trace(ray, record)) {
                Utils::Color color = lightManager.computeLighting(record, scene, ray);
                record.setColor(color);
                hitArray[y][x] = record;
            } else {
                hitArray[y][x] = Utils::HitRecord(); // fond
            }
        }
    }

    // === AFFICHAGE SFML ===
    Renderer::SFMLRenderer sfml;
    sfml.openWindow(res.width, res.height, bgColor);
    while (sfml.isOpen()) {
        while (sfml.pollEvent()) {}
        sfml.clean();
        sfml.drawPixelArray(hitArray);
        sfml.display();
    }
    return 0;
}