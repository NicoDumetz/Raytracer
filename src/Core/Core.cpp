/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include "Core.hpp"

RayTracer::Core::Core(const std::string& filename, char** env)
    : _libLoader(PLUGIN_PATH),
      _parser(std::make_unique<SceneParser>(filename)),
      _primitiveFactory(std::make_shared<Factory<Primitive::IPrimitive>>()),
      _materialFactory(std::make_shared<Factory<Material::IMaterial>>()),
      _lightFactory(std::make_shared<Factory<Light::ILight>>()),
      _cameraFactory(std::make_shared<Factory<Cam::ICamera>>())
{
    checkEnvDisplay(env);
    for (const auto& lib : _libLoader.getAllLibs()) {
        auto type = lib->type();
        auto it = _registry.find(type);
        if (it != _registry.end())
            it->second(*lib);
    }
    _sceneBuilder = std::make_unique<SceneBuilder>(
        _primitiveFactory,
        _lightFactory,
        _materialFactory,
        _cameraFactory,
        _parser->getNodes()
    );
}

void RayTracer::Core::checkEnvDisplay(char **env)
{
    /* ^ start
    ** : first  char
    ** [0-9] one or many num
    ** (.[0-9]+)? option with number after .
    ** $ end
    */
    std::regex displayRegex(R"(^(:[0-9]+(.[0-9]+)?)$)");
    std::string lines;
    bool envDisplay = false;

    for (int i = 0; env[i]; i++) {
        lines = env[i];
        if (lines.rfind("DISPLAY=", 0) == 0 && std::regex_match(lines.substr(8), displayRegex)) {
            envDisplay = true;
            break;
        }
    }
    if (!envDisplay)
        throw std::runtime_error("Error: DISPLAY is missing or invalid. Please run in a graphical environment.");
}

void RayTracer::Core::run()
{
    const RayTracer::Scene& scene = _sceneBuilder->getScene();
    const auto& cam = scene.getCamera();
    const auto res = cam.getResolution();
    const Utils::Color& bgColor = scene.getBackgroundColor();
    std::vector<std::vector<Utils::Color>> pixelArray(res.height, std::vector<Utils::Color>(res.width));
    const int threadCount = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    int rowPerThread = res.height / threadCount;
    auto start = std::chrono::high_resolution_clock::now();

    auto traceSection = [&](int startY, int endY) {
        for (int y = startY; y < endY; y++) {
            for (int x = 0; x < res.width; x++)
                pixelArray[y][x] = lightManager.traceRay(cam.generateRay(x, y), scene, 3);
        }
    };
    for (int i = 0; i < threadCount; i++) {
        int startY = i * rowPerThread;
        int endY = (i == threadCount - 1) ? res.height : startY + rowPerThread;
        threads.emplace_back(traceSection, startY, endY);
    }
    for (auto &t : threads)
        t.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Elapsed time: " << duration.count() << " seconds\n";

    _render->openWindow(res.width, res.height, bgColor);
    while (_render->isOpen()) {
        while (_render->pollEvent()) {}
        _render->clean();
        _render->drawPixelArray(pixelArray);
        _render->display();
    }
}