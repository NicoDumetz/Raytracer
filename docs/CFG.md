# 📄 Scene Configuration File (`.cfg`)

Scenes are defined using the `libconfig++` format. Each file describes the **camera**, **objects**, **lights**, and **materials** used for rendering.

Your `.cfg` must contain at least the following top-level sections:

- `camera` → describes the point of view
- `primitives` → lists all objects to render
- `lights` → sets up illumination

## 📋 Summary of Config Keys & Expected Types

This table lists all valid keys in `.cfg` files and the type they must have.

| Section       | Key              | Type         | Description                                   |
|---------------|------------------|--------------|-----------------------------------------------|
| `global`      | `backgroundColor`| `Color`      | RGBA background color                         |
|               | `antialiasing`   | `Group`      | Contains `type` (string), `samples` (int)     |
| `camera`      | `resolution`     | `Group`      | `{ width = int; height = int; }`             |
|               | `position`       | `Vector3D`   | `{ x = float; y = float; z = float; }`       |
|               | `target`         | `Vector3D`   | The point the camera is looking at                  |
|               | `up`             | `Vector3D`   | The vertical axis of the camera (usually Y-up)      |
|               | `fov`            | `float`      | Field of view in degrees                      |
| `materials`   | `name`           | `string`     | Used to reference in primitives               |
|               | `type`           | `string`     | Plugin type (e.g. `flat`, `glass`)            |
|               | `color`          | `Color`      | Used by most materials                        |
|               | `color1/2`       | `Color`      | Used by checkerboard/perlin                   |
|               | `tileSize`       | `float`      | For procedural materials                      |
|               | `ior`            | `float`      | Index of refraction for `glass`              |
|               | `colorTop/Bottom`| `Color`      | For `gradient` material                       |
| `primitives`  | `type`           | `string`     | e.g. `sphere`, `cube`, etc.                   |
|               | `material`       | `string`     | Refers to a name in `materials`              |
|               | `center`         | `Vector3D`   | Most shapes                                   |
|               | `point`          | `Vector3D`   | For planes                                    |
|               | `normal`         | `Vector3D`   | For planes                                    |
|               | `a/b/c`          | `Vector3D`   | Triangle vertices                             |
|               | `radius`         | `float`      | Sphere, cone, cylinder                        |
|               | `height`         | `float`      | Cone, cylinder                                |
|               | `size`           | `float`      | Cube                                          |
|               | `major_radius`   | `float`      | Torus                                         |
|               | `minor_radius`   | `float`      | Torus                                         |
|               | `minY` / `maxY`  | `float`      | Limited primitives (optional)                |
|               | `translate`      | `Vector3D`   | Optional transform                            |
|               | `scale`          | `Vector3D`   | Optional transform                            |
|               | `rotateX/Y/Z`    | `float`      | Optional transform (in degrees)              |
|               | `rotate`         | `Group`      | `{ axis, angle, center? }` (optional)        |
| `lights`      | `color`          | `Color`      | Light color                                   |
|               | `position`       | `Vector3D`   | Point light                                   |
|               | `direction`      | `Vector3D`   | Directional light                             |

---

**Types reference:**

| Type      | Format example                              |
|-----------|---------------------------------------------|
| `string`  | `"myName"`                                  |
| `float`   | `42.5`                                       |
| `int`     | `1`                                          |
| `Color`   | `{ r = 255; g = 255; b = 255; a = 255; }`    |
| `Vector3D`| `{ x = 0; y = 1; z = 0; }`                   |
| `Group`   | A nested block with multiple fields          |

---


## 🌍 Global Settings

The optional `global` section lets you configure global render options such as background color and antialiasing.

It must be placed at the **top level** of your `.cfg` file.

### 🖌️ `backgroundColor`

Sets the color of the background (used when rays miss all objects).

| Field            | Type  | Default              |
|------------------|-------|----------------------|
| `backgroundColor`| Color | `{ r=0; g=0; b=0; a=255 }` |

```cfg
global: {
  backgroundColor = { r = 13; g = 13; b = 25; a = 255; };
};
```

### 🧪 `antialiasing`

Configure image smoothing using supersampling.

| Field           | Type   | Description                                   |
|-----------------|--------|-----------------------------------------------|
| `type`          | string | `"supersampling"` (only supported method)     |
| `samples`       | int    | Number of samples per pixel (min: 1)          |

```cfg
global: {
  antialiasing = {
    type = "supersampling";
    samples = 4;
  };
};
```

Using `samples = 1` disables antialiasing.

### ✅ Full example:

```cfg
global: {
  backgroundColor = { r = 13; g = 13; b = 25; a = 255; };
  antialiasing = {
    type = "supersampling";
    samples = 2;
  };
};
```

## 🎥 `camera` (required)

```cfg
camera: {
  resolution = { width = 800; height = 600; };
  position = { x = 0; y = 0; z = -100; };
  target = { x = 0; y = 0; z = 0; };
  up = { x = 0; y = 1; z = 0; };
  fov = 60.0;
};
```


| Field       | Required | Description                                      |
|-------------|----------|--------------------------------------------------|
| `width`     | ✅        | Output image width (in pixels)                  |
| `height`    | ✅        | Output image height (in pixels)                 |
| `position`  | ✅        | Camera position in 3D space                     |
| `target`    | ✅        | Point the camera is looking at                 |
| `up`        | ✅        | Up direction (usually `{ x=0, y=1, z=0 }`)      |
| `fov`       | ✅        | Field of view in degrees (horizontal)           |

## 💡 Lights

Lights define how your scene is illuminated. You can combine multiple types of lights.

Each light type has its own section in the `lights` block:

```cfg
lights: {
  ambient = { color = { r = 50; g = 50; b = 50; }; };
  point = (
    { position = { x = 100; y = 100; z = -50; }; color = { r = 255; g = 255; b = 255; }; }
  );
  directional = (
    { direction = { x = -1; y = -1; z = 0; }; color = { r = 255; g = 255; b = 255; }; }
  );
};
```

### 🌫️ `ambient`

Applies a constant base light to the entire scene.  
Useful to ensure that non-lit areas are not pure black.

| Parameter | Type  | Required | Example                         |
|-----------|-------|----------|----------------------------------|
| `color`   | Color | ✅        | `{ r = 40; g = 40; b = 40; }`    |

```cfg
ambient = {
  color = { r = 40; g = 40; b = 40; };
};
```

### 💡 `point` (can be multiple)

Emits light from a specific position in space, in all directions.

| Parameter   | Type     | Required | Example                             |
|-------------|----------|----------|--------------------------------------|
| `position`  | Point3D  | ✅        | `{ x = 50; y = 100; z = -20; }`     |
| `color`     | Color    | ✅        | `{ r = 255; g = 255; b = 255; }`    |

```cfg
point = (
  {
    position = { x = 50; y = 100; z = -20; };
    color = { r = 255; g = 255; b = 255; };
  }
);
```

You can define multiple `point` lights in the same array.

### 🌞 `directional` (can be multiple)

Simulates an infinite parallel light source (like the sun).  
Only the direction matters — not the position.

| Parameter    | Type     | Required | Example                          |
|--------------|----------|----------|----------------------------------|
| `direction`  | Vector3D | ✅        | `{ x = -1; y = -1; z = 0; }`     |
| `color`      | Color    | ✅        | `{ r = 255; g = 255; b = 255; }` |

```cfg
directional = (
  {
    direction = { x = -1; y = -1; z = 0; };
    color = { r = 255; g = 255; b = 255; };
  }
);
```

You can define multiple directional lights in the same array.

## 🎨 Materials

Materials are declared in the top-level `materials` array.

Each material must have:
- `name`: a unique identifier used by primitives
- `type`: the material plugin name (e.g. `flat`, `mirror`, etc.)
Parameters vary depending on the material type.

### 🟥 `flat`

Applies a constant color to the surface (no lighting response).

| Field   | Type  | Required |
|---------|-------|----------|
| `name`  | string| ✅        |
| `type`  | `"flat"` | ✅    |
| `color` | Color | ✅        |

```cfg
{ name = "pink"; type = "flat"; color = { r = 255; g = 105; b = 180; a = 255; }; }
```

### ♟️ `checkerboard`

Applies a 3D checker pattern using two colors and a tile size.

| Field      | Type   | Required | Default                    |
|------------|--------|----------|-----------------------------|
| `name`     | string | ✅        | —                           |
| `type`     | `"checkerboard"` | ✅ | —                      |
| `color1`   | Color  | ❌        | `{ r=255; g=255; b=255; }`  |
| `color2`   | Color  | ❌        | `{ r=0; g=0; b=0; }`        |
| `tileSize` | float  | ❌        | `100.0`                     |

```cfg
{
  name = "damier";
  type = "checkerboard";
  color1 = { r = 255; g = 255; b = 255; a = 255; };
  color2 = { r = 64; g = 64; b = 64; a = 255; };
  tileSize = 100.0;
}
```

### 🪞 `mirror`

Reflective surface that reflects rays (perfect mirror effect).

| Field   | Type  | Required |
|---------|-------|----------|
| `name`  | string| ✅        |
| `type`  | `"mirror"` | ✅  |
| `color` | Color | ✅        |

```cfg
{ name = "mirrorWhite"; type = "mirror"; color = { r = 255; g = 255; b = 255; a = 255; }; }
```

### 🌫️ `perlin`

Applies a 3D procedural noise pattern between two colors.

| Field      | Type   | Required | Default                    |
|------------|--------|----------|-----------------------------|
| `name`     | string | ✅        | —                           |
| `type`     | `"perlin"` | ✅   | —                           |
| `color1`   | Color  | ❌        | `{ r = 255; g = 255; b = 255; a = 255 }` |
| `color2`   | Color  | ❌        | `{ r = 0; g = 0; b = 0; a = 255 }`       |
| `tileSize` | float  | ❌        | `1.0`                       |

```cfg
{
  name = "perlin_rock";
  type = "perlin";
  color1 = { r = 255; g = 255; b = 255; a = 255; };
  color2 = { r = 0; g = 0; b = 0; a = 255; };
  tileSize = 1.0;
}
```

### 🧊 `transparent`

A semi-transparent material with fixed reflectivity and index of refraction.

| Field   | Type  | Required |
|---------|-------|----------|
| `name`  | string| ✅        |
| `type`  | `"transparent"` | ✅ |
| `color` | Color | ✅        |

```cfg
{ name = "ghost"; type = "transparent"; color = { r = 200; g = 200; b = 255; a = 255; }; }
```

### 🔮 `glass`

Refractive material using an index of refraction (IOR).  
It simulates both reflection and transmission using Schlick's approximation.

| Field   | Type  | Required |
|---------|-------|----------|
| `name`  | string| ✅        |
| `type`  | `"glass"` | ✅    |
| `color` | Color | ✅        |
| `ior`   | float | ✅        |

```cfg
{
  name = "glassy";
  type = "glass";
  color = { r = 180; g = 220; b = 255; a = 255; };
  ior = 1.5;
}
```

### 🌈 `gradient`

Applies a vertical gradient between two colors based on the Y position of the surface.

| Field        | Type  | Required |
|--------------|-------|----------|
| `name`       | string| ✅        |
| `type`       | `"gradient"` | ✅ |
| `colorTop`   | Color | ✅        |
| `colorBottom`| Color | ✅        |

```cfg
{
  name = "skyfade";
  type = "gradient";
  colorTop = { r = 135; g = 206; b = 250; a = 255; };
  colorBottom = { r = 25; g = 25; b = 112; a = 255; };
}
```

## 🧱 Primitives

All primitives are declared in a flat array in the `primitives` block.

Each primitive must contain:
- `type`: the primitive plugin name
- `material`: the name of a material declared in `materials`
- The required geometric fields depending on the shape
- Optional transforms (see below)

### 🟠 `sphere`

| Field     | Type    | Required |
|-----------|---------|----------|
| `type`    | `"sphere"` | ✅    |
| `center`  | Point3D | ✅        |
| `radius`  | float   | ✅        |
| `material`| string  | ✅        |

```cfg
{
  type = "sphere";
  center = { x = 0; y = 100; z = 0; };
  radius = 100;
  material = "pink";
}
```

### 🟫 `plane`

| Field     | Type    | Required |
|-----------|---------|----------|
| `type`    | `"plane"` | ✅     |
| `point`   | Point3D | ✅        |
| `normal`  | Vector3D| ✅        |
| `material`| string  | ✅        |

```cfg
{
  type = "plane";
  point = { x = 0; y = -200; z = 0; };
  normal = { x = 0; y = 1; z = 0; };
  material = "damier";
}
```

### 🧊 `cube`

| Field     | Type    | Required |
|-----------|---------|----------|
| `type`    | `"cube"` | ✅      |
| `center`  | Point3D | ✅        |
| `size`    | float   | ✅        |
| `material`| string  | ✅        |

```cfg
{
  type = "cube";
  center = { x = -300; y = 350; z = 100; };
  size = 100.0;
  material = "pink";
}
```

### 🪵 `cylinder`

| Field     | Type    | Required |
|-----------|---------|----------|
| `type`    | `"cylinder"` | ✅  |
| `center`  | Point3D | ✅        |
| `radius`  | float   | ✅        |
| `height`  | float   | ✅        |
| `material`| string  | ✅        |

```cfg
{
  type = "cylinder";
  center = { x = -250; y = 50; z = 50; };
  radius = 70;
  height = 200;
  material = "pink";
}
```

### 🪄 `limited_cylinder`

Like `cylinder`, with optional vertical limits.

| Field   | Description        |
|---------|--------------------|
| `minY`  | Optional bottom Y offset |
| `maxY`  | Optional top Y offset    |

```cfg
{
  type = "limited_cylinder";
  center = { x = 100; y = 100; z = -400; };
  radius = 40;
  height = 200;
  material = "blue";
}
```

### 🥫 `cone`

| Field     | Type    | Required |
|-----------|---------|----------|
| `type`    | `"cone"` | ✅      |
| `center`  | Point3D | ✅        |
| `radius`  | float   | ✅        |
| `height`  | float   | ✅        |
| `material`| string  | ✅        |

```cfg
{
  type = "cone";
  center = { x = -200; y = 100; z = 0; };
  radius = 100;
  height = 200;
  material = "blue";
}
```

### 🔻 `limited_cone`

Like `cone`, with optional caps.

| Field   | Description        |
|---------|--------------------|
| `minY`  | Optional base offset |
| `maxY`  | Optional top offset  |

```cfg
{
  type = "limited_cone";
  center = { x = -100; y = 400; z = 100; };
  radius = 100;
  height = 400;
  material = "pink";
}
```

### 🌀 `torus`

A donut shape defined by two radii.

| Field         | Type    | Required |
|---------------|---------|----------|
| `center`      | Point3D | ✅        |
| `major_radius`| float   | ✅        |
| `minor_radius`| float   | ✅        |

```cfg
{
  type = "torus";
  center = { x = -200; y = 50; z = -500; };
  major_radius = 50.0;
  minor_radius = 10.0;
  material = "pink";
}
```

### 🔺 `triangle`

A flat triangle defined by 3 points.

| Field | Type    | Required |
|-------|---------|----------|
| `a`   | Point3D | ✅        |
| `b`   | Point3D | ✅        |
| `c`   | Point3D | ✅        |

```cfg
{
  type = "triangle";
  a = { x = 100; y = 0; z = 0; };
  b = { x = 100; y = 400; z = 0; };
  c = { x = 100; y = 0; z = -500; };
  material = "perlin_rock";
}
```

## 🔄 Transforms

Each primitive can have optional transform fields to modify its position, orientation, or size.

These transformations are applied **in order** internally:  
**Rotation → Scaling → Translation**

### ✅ Supported keys

| Key         | Type     | Description                                       |
|-------------|----------|---------------------------------------------------|
| `translate` | Vector3D | Moves the object in world space                   |
| `scale`     | Vector3D | Scales the object on X, Y, Z axes                 |
| `rotateX`   | float    | Rotates around the X axis (degrees)               |
| `rotateY`   | float    | Rotates around the Y axis (degrees)               |
| `rotateZ`   | float    | Rotates around the Z axis (degrees)               |
| `rotate`    | block    | Arbitrary axis rotation (see below)               |

### ✏️ Example: simple translation and rotation

```cfg
{
  type = "cube";
  center = { x = 0; y = 0; z = 0; };
  size = 100;
  material = "pink";

  translate = { x = 100; y = 0; z = 0; };
  rotateY = 45.0;
}
```

### 🔄 Arbitrary axis rotation (`rotate` block)

You can also rotate around any axis (normalized) with an optional pivot center.

| Subfield | Type     | Required | Description                     |
|----------|----------|----------|---------------------------------|
| `axis`   | Vector3D | ✅        | Axis of rotation                |
| `angle`  | float    | ✅        | Angle in degrees                |
| `center` | Point3D  | ❌        | Pivot point (default: object center) |

```cfg
rotate = {
  axis = { x = 1; y = 1; z = 0; };
  angle = 60;
  center = { x = 0; y = 0; z = 0; };  // optional
};
```

This rotation is useful for rotating objects in arbitrary directions (e.g., diagonal tilt).

## 📄 Full Example Configuration

Here's a complete example of a `.cfg` file using all major sections:

```cfg
global: {
  backgroundColor = { r = 20; g = 20; b = 30; a = 255; };
  antialiasing = {
    type = "supersampling";
    samples = 2;
  };
};

camera: {
  resolution = { width = 1280; height = 720; };
  position = { x = -100; y = 0; z = -800; };
  target = { x = 0; y = 100; z = 0; };
  up = { x = 0; y = 1; z = 0; };
  fov = 60.0;
};

materials: (
  { name = "pink"; type = "flat"; color = { r = 255; g = 105; b = 180; a = 255; }; },
  { name = "damier"; type = "checkerboard";
    color1 = { r = 255; g = 255; b = 255; a = 255; };
    color2 = { r = 64; g = 64; b = 64; a = 255; };
    tileSize = 100.0;
  },
  { name = "mirrorWhite"; type = "mirror"; color = { r = 255; g = 255; b = 255; a = 255; }; }
);

primitives: (
  {
    type = "sphere";
    center = { x = 0; y = 100; z = 0; };
    radius = 100;
    material = "pink";
    translate = { x = 150; y = 0; z = 0; };
  },
  {
    type = "plane";
    point = { x = 0; y = -200; z = 0; };
    normal = { x = 0; y = 1; z = 0; };
    material = "damier";
  },
  {
    type = "cube";
    center = { x = 0; y = 0; z = 0; };
    size = 100.0;
    material = "mirrorWhite";
    rotateY = 45.0;
  },
);

lights: {
  ambient = {
    color = { r = 40; g = 40; b = 40; a = 255; };
  };
  directional = (
    {
      direction = { x = -1; y = -1; z = 0; };
      color = { r = 255; g = 255; b = 255; a = 255; };
    }
  );
};
```

This file will produce:
- A pink sphere
- A reflective cube
- A checkerboard floor
- A directional light with ambient fill

Feel free to use this as a base for your scenes!
