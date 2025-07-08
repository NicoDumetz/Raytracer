/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#include "Core.hpp"
#include <fstream>
#include <string>

RayTracer::Core::Core(const std::string& filename, const std::string& ppmFilename, char** env)
    : _libLoader(PLUGIN_PATH),
      _parser(std::make_unique<SceneParser>(filename)),
      _ppmFilename(ppmFilename),
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

bool RayTracer::Core::parseArgs(int argc, char **argv, std::string& configFile,
    std::string& ppmFile)
{
    std::string arg;

    for (unsigned char i = 1; i < argc; ++i) {
        arg = argv[i];
        if (arg == "-o") {
            if (i + 1 < argc)
                ppmFile = argv[++i];
            else {
                std::cerr << "Error: Missing argument for -o option" << std::endl;
                return true;
            }
            continue;
        }
        if (arg[0] != '-') {
            if (!configFile.empty()) {
                std::cerr << "Error: Redefinition of scene config file" << std::endl;
                return true;
            }
            configFile = arg;
            continue;
        }
        std::cerr << "Error: Unknown option: " << arg << std::endl;
        return true;
    }
    if (configFile.empty()) {
        std::cerr << "Error: Missing scene config file" << std::endl;
        return true;
    }
    return false;
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

void RayTracer::Core::writePPM(const std::vector<std::vector<Utils::Color>> &pixelsArray) const
{
    std::ofstream file(this->_ppmFilename);

    if (!file.is_open())
        throw std::runtime_error("Unable to open file " + this->_ppmFilename);
    file << "P3\n";
    file << pixelsArray[0].size() << " " << pixelsArray.size() << "\n";
    file << "255\n";

    for (const auto& row : pixelsArray) {
        for (const auto& pixel : row) {
            file << static_cast<int>(pixel.r * 255) << " "
                 << static_cast<int>(pixel.g * 255) << " "
                 << static_cast<int>(pixel.b * 255) << "\n";
        }
    }
    file.close();
    return (void) pixelsArray;
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

    this->writePPM(pixelArray);
    _render->openWindow(res.width, res.height, bgColor);
    while (_render->isOpen()) {
        while (_render->pollEvent()) {}
        _render->clean();
        _render->drawPixelArray(pixelArray);
        _render->display();
    }
}
