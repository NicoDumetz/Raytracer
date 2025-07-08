
# 🧩 Technical Documentation

This document explains the internal architecture of the raytracer engine, how plugins interact with the core, and how to extend the system (e.g., add a new primitive, light, or material).

## 🏗️ Architecture Overview

The raytracer is built around a **modular, plugin-based architecture**, designed to be:

- **Extensible**: Add new shapes, materials, or lights without touching core code.
- **Decoupled**: Each component follows an interface contract and is dynamically loaded.
- **Configurable**: Scenes are defined via `.cfg` files parsed by `libconfig++`.

## 🧠 Core Program

The raytracer's execution is managed by the `Core` class. It orchestrates all stages of rendering, from initialization to image output.

1. **Factory Initialization**
   - The core starts by initializing all plugin factories:
     - `PrimitiveFactory`, `MaterialFactory`, `LightFactory`, etc.
   - It loads all `.so` files from the `./plugins/` directory and calls `registerPlugin()` for each.

2. **Scene Parsing**
   - The `.cfg` file is parsed using `libconfig++` via the `SceneParser` class.
   - It extracts:
     - `global` settings
     - `camera` parameters
     - `materials`, `lights`, `primitives`
   - All entries are wrapped into `ConfigNode` objects.

3. **Scene Building**
   - The list of `ConfigNode` objects is passed to the **SceneBuilder**.
   - Each plugin is instantiated using its factory and the corresponding config node.
   - The builder creates:
     - A full list of `IPrimitive` objects
     - A list of lights
     - The camera object
     - The renderer

4. **Rendering**
   - The renderer starts the image generation:
     - The camera generates one or more rays per pixel.
     - Each ray is tested against the primitives to find the closest intersection.
     - Lighting and materials are applied to compute the final color.

5. **Output**
   - The image is written to a `.ppm` file (default: `output.ppm`).
   - If a renderer plugin like SFML is enabled, a window may display the image.

## 🎯 Rendering Logic

The rendering phase consists in computing the final color of each pixel by tracing a ray from the camera and simulating its interaction with the scene.

At a high level:

```text
Pixel color = Ray → Hit → Material shading → Lighting evaluation → Final color
```

---

### ☄️ Ray Generation and Scene Traversal

For each pixel `(x, y)`, the camera computes a ray pointing into the scene:

```cpp
Ray Camera::generateRay(int x, int y) const;
```

This ray is passed to the scene, which checks for intersections:

```cpp
bool Scene::trace(const Ray& ray, HitRecord& record) const;
```

The scene traverses all objects and checks whether the ray intersects them, storing the **closest intersection** in a `HitRecord`.


### 📍 `HitRecord` – Intersection Information

`HitRecord` is a structure used to store all relevant data when a ray hits an object.  
It is passed around during intersection, shading, and lighting.

Defined in: ```include/Tools/HitRecord.hpp```

```cpp
class HitRecord {
  private:
      float distance;
      math::Point3D position;
      math::Vector3D normal;
      Color color;
      std::shared_ptr<Material::IMaterial> _material;

  public:
      HitRecord() = default;
      ~HitRecord() = default;
      HitRecord(float dist, const math::Point3D& pos, const math::Vector3D& nrm, const Color& col);

      float getDistance() const { return distance; }
      const math::Point3D& getPosition() const { return position; }
      const math::Vector3D& getNormal() const { return normal; }
      const Color& getColor() const { return color; }
      Material::IMaterial& getMaterial() { return *_material; }

      void setDistance(float dist) { distance = dist; }
      void setPosition(const math::Point3D& pos) { position = pos; }
      void setNormal(const math::Vector3D& nrm) { normal = nrm; }
      void setColor(const Color& col) { color = col; }
      void setMaterial(std::shared_ptr<Material::IMaterial> material) {_material = std::move(material);};
  };
```

### 🎨 Material Evaluation

Once a hit is found, the material is used to determine the base appearance of the surface.

The material uses:
- `position` and `normal` (from the `HitRecord`)
- The viewing direction (via the incoming ray)
- A mutable structure called `MaterialProperties` to specify reflection, transparency, etc.

It returns the **base surface color**, before lighting.
### 💡 Lighting Contribution

The lighting for a given hit point is computed using a centralized `LightManager` class.  
It evaluates how each light affects the surface and also handles **reflection** and **refraction** when requested by the material.

### 🔦 LightManager

Defined in: ```include/LightManager.hpp```

```cpp
class LightManager {
public:
    struct MaterialProperties {
        float reflectivity    = 0.0f;
        float transparency    = 0.0f;
        float refractiveIndex = 1.0f;
    };

    static std::optional<math::Vector3D> refract(
        const math::Vector3D& I,
        const math::Vector3D& N,
        float eta
    );

    Utils::Color computeDirectLighting(
        const Utils::HitRecord& hit,
        const Scene& scene
    ) const;

    Utils::Color traceRay(
        const Utils::Ray& ray,
        const Scene& scene,
        int depth = 0
    ) const;
};
```

### ☀️ Direct Lighting

The function:

```cpp
Color LightManager::computeDirectLighting(const HitRecord& hit, const Scene& scene) const;
```

- Loops over all lights
- Sends shadow rays to each one
- Accumulates their contribution (if not blocked)
- Applies Lambertian diffuse or other models


### 🪞 Reflection and 🔮 Refraction

The light manager handles them recursively using:

```cpp
Color LightManager::traceRay(const Ray& ray, const Scene& scene, int depth = 0) const;
```

This function:
- Traces the initial ray
- Evaluates lighting at the hit point
- If needed, spawns:
  - A **reflected ray** (via `reflect(view, normal)`)
  - A **refracted ray** (via `refract(...)`, see below)
- Combines their results based on the material’s reflectivity/transparency

Refraction is calculated using:

```cpp
std::optional<Vector3D> LightManager::refract(
    const Vector3D& incident,
    const Vector3D& normal,
    float eta
);
```

### ♻️ Depth Limit

`traceRay` is **recursive**.  
To prevent infinite bouncing, a `depth` parameter limits recursion. A typical max depth is `5`.

If `depth >= MAX_DEPTH`, only direct lighting is computed.

This mechanism allows the engine to support:

- **Perfect mirrors**
- **Transparent glass**
- **Fresnel blends**
- **Recursive ray effects**

All while remaining clean and centralized in the `LightManager`.

### 🧮 Final Pixel Color

Once a ray hits a surface, the final color of the pixel is computed by combining multiple contributions:

1. **Ambient light** (constant base light)
2. **Direct lighting** from all visible lights
3. **Material shading** at the intersection point
4. **Optional** reflection and/or refraction

```text
finalColor =
    material.shade(hit, view) × (ambient + ∑ visibleLight_i)
  + reflectionColor × reflectivity
  + refractionColor × transparency
```

- **`material.shade(...)`** returns the base surface color based on position, normal, and view direction.
- **`ambient` + ∑ lights** comes from `LightManager::computeDirectLighting(...)`
- If the material sets `reflectivity > 0`, the renderer calls `traceRay(...)` on the **reflected ray**
- If the material sets `transparency > 0`, it computes the **refracted ray** via `refract(...)` and traces it as well
- The final color is a **weighted combination** of all three:
  - Direct lighting
  - Reflection
  - Refraction

### 🎚️ Postprocessing

- The final color is **clamped** per channel to `[0, 255]`
- Optionally, a **gamma correction** is applied to match human perception
- The result is written to the image buffer (or displayed by a renderer plugin)

---

## 🔌 Plugin System

The raytracer is built around a **dynamic plugin system** that allows new components (shapes, lights, materials, etc.) to be added **without recompiling the engine**.

This design enables:
- Clean separation between core logic and extensible behavior
- Easy experimentation with new rendering features
- A modular architecture where each plugin is independent and self-contained

Plugins are compiled as **shared libraries (`.so`)** and loaded dynamically at runtime.


### 🎯 Plugin Category

Each major component of the raytracing pipeline is implemented as a plugin:

| Plugin Category | Purpose                                | Examples                     |
|------------------|-----------------------------------------|------------------------------|
| `primitive`      | Defines a shape the ray can hit         | `sphere`, `plane`, `cube`    |
| `material`       | Defines how surfaces react to light     | `flat`, `glass`, `perlin`    |
| `light`          | Defines a light source in the scene     | `ambient`, `directional`     |
| `camera`         | Defines how rays are generated           | `pinhole`                    |
| `renderer`       | Defines how the image is displayed       | `SFML` viewer                |

Each plugin implements a specific **C++ interface** (e.g., `IPrimitive`, `IMaterial`, `ILight`, etc.).

### 🧠 How plugins are loaded

At startup, the engine:
1. Scans the `./plugins/` directory
2. Loads each `.so` file using `dlopen`
3. Looks for three C-style functions:

```cpp
extern "C" {
    void registerPlugin(FactoryInterface& factory); // registers the plugin
    RayTracer::Ltype type();                        // returns the plugin type
    const char* name();                             // returns the plugin name
}
```

4. Registers the plugin with the appropriate factory
5. Instantiates objects on demand based on `.cfg` file content

### 🛠️ How to Add a Plugin

Once your plugin is written or compiled, there are **two ways** to make it available to the engine:


#### ✅ Option 1: Drop-in `.so` file

1. Compile your plugin into a `.so` file (shared library)
2. Place it manually into the `./plugins/` directory

The engine will:
- Load it dynamically via `dlopen`
- Detect its type and name using exported functions
- Register it using its factory

This is ideal for quick experiments or external contributions.

#### 🧱 Option 2: Add it to the CMake build system

The main `CMakeLists.txt` provides a centralized system to declare plugins using a helper function:

### 🔧 CMake Plugin Management

Defined once:

```cmake
########################################################################################
##                                                                                    ##
##     PLUGIN MANAGEMENT FUNCTION                                                     ##
##     Reusable function to add any plugin easily                                     ##
##                                                                                    ##
########################################################################################

function(add_raytracer_plugin target subdir link_libs)
    file(GLOB_RECURSE SRC "${PLUGIN_DIR}/${subdir}/*.cpp")
    add_library(${target} SHARED ${SRC})
    set_target_properties(${target} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR}
        PREFIX ""
    )
    target_link_libraries(${target} raytracer_common ${link_libs})
endfunction()
```

You can then declare all plugins using:

```cmake
########################################################################################
##                                                                                    ##
##     PLUGINS : DYNAMIC MODULES                                                      ##
##     All shared object (.so) plugins dynamically loaded by the raytracer engine     ##
##                                                                                    ##
########################################################################################

# ╭────────────── PRIMITIVES ──────────────╮
add_raytracer_plugin(r_p_sphere           "Primitives/Sphere"           "")
add_raytracer_plugin(r_p_plane            "Primitives/Plane"            "")
add_raytracer_plugin(r_p_cone             "Primitives/Cone"             "")
add_raytracer_plugin(r_p_cylinder         "Primitives/Cylinder"         "")
add_raytracer_plugin(r_p_triangles        "Primitives/Triangles"        "")
add_raytracer_plugin(r_p_Cube             "Primitives/Cube"             "")
add_raytracer_plugin(r_p_LimitedCone      "Primitives/LimitedCone"      "")
add_raytracer_plugin(r_p_LimitedCylinder  "Primitives/LimitedCylinder"  "")
add_raytracer_plugin(r_p_Torus            "Primitives/Torus"            "")
# ╰───────────────────────────────────────────╯

# ╭──────────────── CAMERA ────────────────╮
add_raytracer_plugin(r_c_camera           "Camera"                      "")
# ╰───────────────────────────────────────────╯

# ╭─────────────── MATERIALS ──────────────╮
add_raytracer_plugin(r_m_flatcolor        "Material/FlatColor"          "")
add_raytracer_plugin(r_m_Checkboard       "Material/Checkboard"         "")
add_raytracer_plugin(r_m_glass            "Material/Glass"              "")
add_raytracer_plugin(r_m_perlin           "Material/Perlin"             "")
add_raytracer_plugin(r_m_mirror           "Material/Mirror"             "")
add_raytracer_plugin(r_m_transparent      "Material/Transparent"        "")
add_raytracer_plugin(r_m_gradient         "Material/Gradient"           "")
# ╰───────────────────────────────────────────╯

# ╭──────────────── LIGHTS ───────────────╮
add_raytracer_plugin(r_l_ambient          "Light/AmbientLight"          "")
add_raytracer_plugin(r_l_directional      "Light/DirectionnalLight"     "")
add_raytracer_plugin(r_l_pointLight       "Light/PointLight"            "")
# ╰──────────────────────────────────────────╯

# ╭────────────── RENDERER ───────────────╮
add_raytracer_plugin(r_r_sfml             "Renders/SFML"                "sfml-graphics;sfml-window;sfml-system")
# ╰──────────────────────────────────────────╯
```

This system ensures that:
- Plugins are **compiled automatically**
- Placed into the correct `./plugins/` directory
- Use consistent naming (`r_p_`, `r_m_`, `r_l_`, etc.)


### 🏷️ Naming Convention

To ensure consistency and automatic detection, plugin naming follows strict conventions — both for filenames and internal registration.


When compiled, each plugin is built as a `.so` file named:

```text
r_<category>_<name>.so
```

| Category   | Prefix  | Example Plugin Filename     |
|------------|---------|-----------------------------|
| Primitive  | `r_p_`  | `r_p_sphere.so`             |
| Material   | `r_m_`  | `r_m_flatcolor.so`          |
| Light      | `r_l_`  | `r_l_pointLight.so`         |
| Camera     | `r_c_`  | `r_c_camera.so`             |
| Renderer   | `r_r_`  | `r_r_sfml.so`               |

The engine uses this naming pattern to help categorize and validate the plugin before loading.

## 🛠️ How to Create a Plugin

Creating a plugin (primitive, material, light, etc.) involves implementing a specific interface, registering it via `registerPlugin()`, and using a `ConfigNode` to receive its parameters from the `.cfg` scene file.

We'll start by explaining the `ConfigNode`, which is the key to accessing config values when building a plugin.


### 📦 `ConfigNode` Wrapper

Every plugin constructor receives an instance of `Utils::ConfigNode`, which contains the fields extracted from the `.cfg` file.

This allows you to access parameters like `radius`, `color`, `translate`, etc. in a uniform way.


### 📄 Header: `ConfigNode.hpp`

```cpp
class ConfigNode {
public:
    enum class ConfigType {
        CAMERA,
        SCENE,
        PRIMITIVE,
        LIGHT,
        MATERIAL,
        GLOBAL,
        UNKNOWN
    };

    ConfigNode(ConfigType type, const std::string& name);

    const std::string& getName() const {return _name;}
    ConfigType getType() const {return _type;}

    bool has(const std::string& key) const;
    const std::string &get(const std::string& key) const;

    const std::unordered_map<std::string, std::string>& getFields() const;
    void setField(const std::string& key, const std::string& value);

    void setMaterial(std::shared_ptr<Material::IMaterial> material);
    const std::shared_ptr<Material::IMaterial>& getMaterial() const;

    Utils::Color parseColor(const std::string& field) const;
    math::Vector3D parseVector3(const std::string& field) const;
    math::Point3D parsePoint3D(const std::string& field) const;
    float parseFloat(const std::string& field) const;
    int parseInt(const std::string& field) const;

private:
    ConfigType _type;
    std::string _name;
    std::unordered_map<std::string, std::string> _fields;
    std::shared_ptr<Material::IMaterial> _material;
};
```

The `ConfigNode` acts as a lightweight, type-safe map of config keys to values.

---

### 🧪 Example Usage in a Plugin

Suppose your `.cfg` contains:

```cfg
{
  type = "sphere";
  center = { x = 0; y = 0; z = 0; };
  radius = 50;
  material = "pink";
}
```

Your plugin constructor might look like:

```cpp
Sphere::Sphere(const Utils::ConfigNode& node)
  : APrimitive(node.getMaterial(), node.parsePoint3D("center"))
{
    _radius = node.parseFloat("radius");
}
```

- `parsePoint3D("center")` gives you a `Point3D`
- `parseFloat("radius")` gives you a float
- `getMaterial()` returns the material object already built


## 🧩 Plugin Types

Each plugin type implements a different interface and serves a distinct role in the rendering pipeline.

### 🖼️ Renderer Plugin (`IRenderer`)

A renderer plugin is responsible for **displaying or saving the final image**.  
This may be:
- A live window (e.g. using SFML)
- Saving the image to a file (e.g. `.ppm`, `.png`, etc.)
- Both simultaneously

The engine delegates all image presentation to a plugin implementing the `IRenderer` interface.

#### 📄 Interface: `IRenderer.hpp`

```cpp
class IRenderer
{
public:
    virtual ~IRenderer() = default;

    virtual void openWindow(unsigned int width, unsigned int height, const Utils::Color& background) = 0;
    virtual void closeWindow() = 0;
    virtual bool isOpen() const = 0;
    virtual bool pollEvent() = 0;
    virtual void clean() = 0;
    virtual void drawPixelArray(const std::vector<std::vector<Utils::Color>>& pixelsArray) = 0;
    virtual void display() = 0;
    virtual void saveImage(std::string path) const = 0;
};
```
#### 📚 Method Breakdown

| Method              | Description                                                       |
|---------------------|-------------------------------------------------------------------|
| `openWindow(...)`   | Initializes the renderer with resolution and background color     |
| `closeWindow()`     | Closes the window or releases rendering resources                 |
| `isOpen()`          | Returns `true` if the window is still open (for live display loop)|
| `pollEvent()`       | Processes window events (close, input, etc.)                      |
| `clean()`           | Clears the current frame before drawing                           |
| `drawPixelArray()`  | Draws a 2D color array (the full image buffer)                    |
| `display()`         | Renders the final buffer to the screen                            |
| `saveImage(path)`   | Writes the final image to disk at the given path                  |

---

#### 📝 Notes

- The renderer is **optional**: if none is specified, output can default to a `.ppm` file.
- `drawPixelArray()` is typically called once per frame (after rendering is complete).
- `pollEvent()` is used for closing the window cleanly or handling user input.
- All colors in the pixel array are already computed and clamped by the engine.

### 🎥 Camera Plugin (`ICamera`)

A camera plugin defines the **viewpoint** of the scene and generates **primary rays** for each pixel.  
It controls how the world is projected into the image — typically via a **perspective (pinhole)** model.

---

#### 📄 Interface: `ICamera.hpp`

```cpp
class ICamera {
public:
    struct Resolution {
        int width;
        int height;
    };
  public:
    virtual ~ICamera() = default;
    virtual Utils::Ray generateRay(int x, int y) const = 0;
    virtual const Resolution getResolution() const = 0;
};
```

#### 📚 Method Breakdown

| Method                  | Description                                               |
|-------------------------|-----------------------------------------------------------|
| `generateRay(x, y)`     | Returns a `Ray` starting from the camera through pixel (x, y) |
| `getResolution()`       | Returns the width and height of the final image           |

---

### 🧠 Notes

- The renderer uses `getResolution()` to know how many pixels to generate.
- `generateRay()` is called once per sample, per pixel.
- The camera typically uses parameters like:
  - `position`: 3D location of the camera
  - `target`: point the camera looks at
  - `up`: orientation vector
  - `fov`: horizontal field of view in degrees

#### 🧪 Example constructor usage

If the camera is configured in `.cfg` like this:

```cfg
camera: {
  resolution = { width = 800; height = 600; };
  position = { x = 0; y = 0; z = -100; };
  target = { x = 0; y = 0; z = 0; };
  up = { x = 0; y = 1; z = 0; };
  fov = 60.0;
};
```

The plugin constructor might extract these values with:

```cpp
Camera::Camera(const Utils::ConfigNode& node) {
    _resolution = {
        std::stoi(node.get("width")),
        std::stoi(node.get("height"))
    };

    _position = node.parsePoint3D("position");
    _forward = (node.parsePoint3D("target") - _position).normalized();
    _right   = node.parseVector3("up").cross(_forward).normalized();
    _up      = _forward.cross(_right).normalized();
}
```

### 💡 Light Plugin (`ILight`)

Light plugins define **how illumination is produced** in the scene.

Each light calculates its contribution for a surface point during shading, based on geometry, direction, and occlusion (shadows).

#### 📄 Interface: `ILight.hpp`

```cpp
class ILight {
public:
    virtual ~ILight() = default;

    virtual Utils::Color illuminate(const Utils::HitRecord& hit, const RayTracer::Scene& scene) const = 0;
};
```

#### 📚 Method Breakdown

| Method             | Description                                                |
|--------------------|------------------------------------------------------------|
| `illuminate(...)`  | Computes the color contribution of the light at a surface point |

- `hit` provides:
  - The position and normal of the point to shade
  - The surface material (if needed)
- `scene` can be used to send **shadow rays** (to check occlusion)


### 🧪 Minimal example: directional light

```cpp
Utils::Color DirectionalLight::illuminate(
    const Utils::HitRecord& hit,
    const RayTracer::Scene& scene
) const {
    Vector3D L = -_direction.normalized();
    Vector3D N = hit.getNormal().normalized();
    Point3D P = hit.getPosition();

    Ray shadowRay(P + L * 1e-4, L);
    HitRecord tmp;
    if (scene.trace(shadowRay, tmp))
        return Utils::Color(0, 0, 0, 1.0f); // in shadow

    float dotNL = std::max(0.0f, N.dot(L));
    return _intensity * dotNL;
}
```

### 🎨 Material Plugin (`IMaterial`)

Materials define **how surfaces react to light** when hit by a ray.  
They control the **base color**, and can optionally request:
- Reflection
- Transparency
- Refraction (glass, water, etc.)

#### 📄 Interface: `IMaterial.hpp`

```cpp
class IMaterial {
public:
    struct MaterialProperties {
        float reflectivity    = 0.0f;
        float transparency    = 0.0f;
        float refractiveIndex = 1.0f;
    };

    virtual ~IMaterial() = default;

    virtual const Utils::Color& shade(
        const Utils::HitRecord& hit,
        const Utils::Ray& viewRay,
        MaterialProperties& props
    ) const = 0;
};
```

#### 📚 Method Breakdown

| Method        | Description                                                                 |
|---------------|-----------------------------------------------------------------------------|
| `shade(...)`  | Returns the base surface color at the hit point                             |
|               | Fills `MaterialProperties` if reflection/refraction is desired              |

- `hit` contains the surface point and its normal
- `viewRay` is the incoming ray from the camera (used for specular/reflection)
- `props` is passed by reference and can be modified by the material

---

### 🔍 MaterialProperties

This struct allows materials to influence ray behavior:

| Field             | Purpose                                |
|------------------|-----------------------------------------|
| `reflectivity`    | Value from `0.0` (none) to `1.0` (mirror) |
| `transparency`    | Amount of transmitted light (`0.0`–`1.0`) |
| `refractiveIndex` | Index of refraction for transparent objects (e.g. `1.5` for glass) |

These values are used by `LightManager::traceRay(...)` to recursively compute reflection/refraction.

### 🧪 Minimal Example: Mirror Material

```cpp
const Utils::Color& Mirror::shade(
    const Utils::HitRecord&,
    const Utils::Ray&,
    IMaterial::MaterialProperties& props
) const {
    props.reflectivity = 1.0f;
    props.transparency = 0.0f;
    props.refractiveIndex = 1.0f;
    return _color;
}
```

This material returns a constant color, but reflects the scene entirely like a mirror.

### 🧱 Primitive Plugin (`IPrimitive`)

Primitive plugins define **geometric objects** that can be intersected by rays: spheres, planes, cubes, etc.  
They must be able to:
- Detect ray hits
- Support geometric transformations
- Expose a bounding box for acceleration structures

#### 📄 Interface: `IPrimitive.hpp`

```cpp
  class IPrimitive {
  public:
      virtual ~IPrimitive() = default;

      virtual bool hit(const Utils::Ray& ray,  Utils::HitRecord& record) const = 0;
      virtual void applyTransform(const math::TransformMatrix &transform) = 0;
      virtual const Utils::AABB getBoundingBox() const = 0;
  };
```

---

### 🧰 `APrimitive` – Helper Base Class

To simplify common logic (like storing material, position, and transforms), a base class `APrimitive` is provided:

```cpp
class APrimitive : public IPrimitive {
protected:
    math::TransformMatrix _transform;
    math::TransformMatrix _inverseTransform;
    std::shared_ptr<Material::IMaterial> _material;
    math::Point3D _position;

    using TransformFn = std::function<void(math::TransformMatrix&, const Utils::ConfigNode&, const math::Point3D&)>;
    const std::unordered_map<std::string, TransformFn> _transformHandler = {
        {"translate", [](math::TransformMatrix& T, const Utils::ConfigNode& node, const math::Point3D&) {
            T.applyTranslation(node.parseVector3("translate"));
        }},
        {"rotateX", [](math::TransformMatrix& T, const Utils::ConfigNode& node, const math::Point3D& pos) {
            math::Point3D center = node.has("center") ? node.parsePoint3D("center") : pos;
            T.rotateAroundPointX(center, node.parseFloat("rotateX") * M_PI / 180.0f);
        }},
        {"rotateY", [](math::TransformMatrix& T, const Utils::ConfigNode& node, const math::Point3D& pos) {
            math::Point3D center = node.has("center") ? node.parsePoint3D("center") : pos;
            T.rotateAroundPointY(center, node.parseFloat("rotateY") * M_PI / 180.0f);
        }},
        {"rotateZ", [](math::TransformMatrix& T, const Utils::ConfigNode& node, const math::Point3D& pos) {
            math::Point3D center = node.has("center") ? node.parsePoint3D("center") : pos;
            T.rotateAroundPointZ(center, node.parseFloat("rotateZ") * M_PI / 180.0f);
        }},
        {"scale", [](math::TransformMatrix& T, const Utils::ConfigNode& node, const math::Point3D&) {
            T.applyScaling(node.parseVector3("scale"));
        }},
    };

public:
    APrimitive(std::shared_ptr<Material::IMaterial> material, math::Point3D position)
        : _material(std::move(material)), _position(position) {};
    ~APrimitive() = default;
    const Material::IMaterial &getMaterial() const { return *_material; }
    void setMaterial(std::shared_ptr<Material::IMaterial> material) {
        _material = std::move(material);
    }
    const math::Point3D& getPosition() const { return _position; }
    void setPosition(const math::Point3D& pos) { _position = pos; }
    virtual bool hit(const Utils::Ray& ray, Utils::HitRecord& record) const = 0;
    virtual void applyTransform(const math::TransformMatrix& M) {
        _transform = M * _transform;
        _inverseTransform = _transform.inverse();
    }
    void applyNodeTransform(const Utils::ConfigNode& node, const math::Point3D position)
    {
        math::TransformMatrix T;

        for (const auto& [key, fn] : _transformHandler) {
            if (node.has(key))
                fn(T, node, position);
        }
        applyTransform(T);
    }
};
```

---

### 🧠 Transform Management

The method `applyNodeTransform()` uses `_transformHandler` to apply transforms defined in the `.cfg` file, such as:

- `translate = { x, y, z }`
- `rotateX = 45`
- `rotateY = ...`
- `scale = { x, y, z }`

It automatically builds and applies a `TransformMatrix` to the primitive.

The inverse is precomputed to allow fast transformation of rays into **object space**.

---

### 🧪 Typical Usage in a Plugin (e.g. `Sphere`)

```cpp
Sphere::Sphere(const Utils::ConfigNode& node)
  : APrimitive(node.getMaterial(), node.parsePoint3D("center"))
{
    _radius = node.parseFloat("radius");
    this->applyNodeTransform(node, _position);
}
```

In `hit(...)`, the ray is first transformed:

```cpp
Ray localRay = _inverseTransform.transform(ray);
```

And the final hit position is reprojected back to world space:

```cpp
Point3D worldHit = _transform.transform(localHit);
Vector3D worldNormal = _transform.rotateVector(localNormal).normalized();
```

---

### 📦 Bounding Box

Each primitive must return an **AABB (Axis-Aligned Bounding Box)** using:

```cpp
const Utils::AABB getBoundingBox() const override;
```

This is used by the BVH (Bounding Volume Hierarchy) system to accelerate ray intersection tests.

> ⚠️ The bounding box must be **transformed** if the object has been rotated or scaled.


In the next section, we'll walk through a full example: writing a new `Primitive` plugin from scratch.

---

## ⚡ Rendering Optimizations

To ensure performance and scalability, the raytracer implements several optimizations at different levels of the pipeline — from geometric acceleration to shading and multithreading.

This section documents all the techniques used to **accelerate rendering** without sacrificing visual quality.

### 📦 BVH – Bounding Volume Hierarchy

All primitives in the scene are organized into a **BVH tree** (Bounding Volume Hierarchy).  
Instead of testing every ray against every object, the BVH allows early pruning using **axis-aligned bounding boxes (AABB)**.

- Each node of the BVH contains a bounding box and either:
  - A list of primitives
  - Two child BVH nodes
- Ray-AABB intersection is very fast
- Only primitives inside intersected boxes are tested with actual `hit(...)` logic

Implemented in the `BVHNode` and `Scene::trace()` traversal logic.

### 🧩 Clustering

**Clustering** is used to group primitives spatially:

- Groups of similar primitives (e.g., adjacent cubes) are stored and indexed together
- The clusters are packed into fewer BVH leaves
- It drastically reduces traversal overhead

> This optimization is particularly effective when rendering large grids of geometry (e.g., cubes).

### 🔁 Multithreading

The raytracer uses **multi-core parallelism** to render faster:

- Each thread is assigned a block of image rows or tiles
- Threads process their pixels independently
- Shared access (e.g. renderer backbuffer) is controlled via mutexes or per-thread buffers

OpenMP or `std::thread` based depending on implementation.

### 🧱 AABB Support in Primitives

Each primitive implements:

```cpp
const Utils::AABB getBoundingBox() const override;
```

Bounding boxes are critical for:
- BVH construction
- Ray vs. box culling before detailed `hit()`

If a primitive is transformed (rotation, scale), its AABB is recomputed to encapsulate the new bounds.

---

### 🪞 Depth-Limited Recursion

Reflection and refraction (in `IMaterial`) are evaluated recursively via:

```cpp
Color LightManager::traceRay(ray, scene, depth);
```

- If `depth >= MAX_DEPTH` (e.g. 5), recursion stops
- Prevents infinite bounces in mirror-glass cycles
- Depth is incremented each time a new ray is spawned


