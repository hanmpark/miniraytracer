<h1 align="center">RT</h1>

<p align="center">
    <b><i>A minimal ray tracer implementing 3D rendering, lighting, and camera simulation.</i></b>
</p></br>

<div align="center">
    <img alt="Repository created at" src="https://img.shields.io/github/created-at/hanmpark/miniraytracer"/>
    <img alt="Repository code size" src="https://img.shields.io/github/languages/code-size/hanmpark/miniraytracer"/>
    <img alt="Mostly used language" src="https://img.shields.io/github/languages/top/hanmpark/miniraytracer"/>
</div>

## 📖 Description
> RT is a CPU ray tracer written in C for the 42 RT project. It parses `.rt`scene files and renders spheres, planes, cylinders, and cones with lighting, shadows, reflections, and procedural checker textures. MiniLibX is used for display on Linux and macOS.

Here are examples of what our `RT` can do:

<div align="center">
    <img src="https://github.com/hanmpark/miniraytracer/blob/master/rt.png" alt="RT rendering"/>
    <img src="https://github.com/hanmpark/miniraytracer/blob/master/objects.png" alt="RT objects"/>
</div>

<div align="center">
    <video controls muted loop width="720">
        <source src="https://github.com/hanmpark/miniraytracer/blob/master/rt.mp4" type="video/mp4">
        Your browser does not support the video tag.
    </video>
</div>

## 🛠️ Features
- **Shapes**: sphere, plane, cylinder, cone.
- **Materials**: diffuse color, specular highlights, reflections, checker pattern.
- **Lighting**: ambient light + multiple colored point lights.
- Hard **shadows** and recursive **reflections** (configurable depth).
- 2x2 **antialiasing** (4 samples per pixel).
- Fast preview mode for interactive camera movement.
- Multithreaded rendering (see `NUM_THREADS` in `include/mrt.h`).
- Finite cylinders and cones with end caps.
- Progressive refresh while rendering.
- Render time logging per frame.
- Tunable parameters (resolution, threads, AA samples, reflection depth, pixel step).
- Shadow bias to reduce self-shadowing artifacts.

## Build
```sh
make
```

Common targets:
```sh
make clean
make fclean
make re
```

## Run
```sh
./rt scenes/spaceship.rt
```

More scenes are available in `scenes/`.

## Controls
- `Esc`: quit.
- `F`: toggle fast mode (lower quality, faster renders, enables movement).
- `W/A/S/D`: move camera (fast mode only).
- `Space/Ctrl`: move up/down (fast mode only).
- Arrow keys: adjust look direction (fast mode only).
- `Q/E`: adjust look direction on Y axis (fast mode only).

Fast mode disables antialiasing and specular highlights, reduces reflection
depth, and increases pixel step size for speed.

## Scene format
Each scene must have exactly one **ambient light** (`A`) and **one camera** (`C`),
**at least one light** (`L`), and **at least one object**. Lines starting with `#`
are comments. The file must end with `.rt`.

```txt
# Ambient: A ratio(0..1) R,G,B(0..255)
A 0.2 255,255,255

# Camera: C pos(x,y,z) look(x,y,z) fov(0..180)
C 0,-5,0 0,0,0 70

# Light: L pos(x,y,z) ratio(0..1) R,G,B(0..255)
L 0,-10,5 1.0 255,255,255

# Sphere: sp pos diameter R,G,B shininess(0..256) reflection(0..1) checker(0|1)
sp -3,0,0 1 255,64,128 32 0.3 0

# Plane: pl pos orient(x,y,z) R,G,B shininess reflection checker
pl 0,0,-2 0,0,0 255,255,255 0 0 1

# Cylinder: cy pos orient(x,y,z) diameter height R,G,B shininess reflection checker
cy 0,0,0 0,0,0 1 1 128,255,64 64 0.2 0

# Cone: co pos orient(x,y,z) diameter height R,G,B shininess reflection checker
co 3,0,0 0.3,0,0 1 1 64,128,255 32 0.2 0
```

Notes:
- `look` and `orient` components must be in the range `-1.0` to `1.0`.
- Colors are integers in `0..255`.
- `checker` toggles a procedural checker texture.

## 👤 Authors
- [hanmpark](https://github.com/hanmpark)
- [YounesBouhlel](https://github.com/YounesBouhlel)
- [Shazway](https://github.com/Shazway)
- [evnsh](https://github.com/evnsh)
