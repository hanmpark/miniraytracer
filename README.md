# miniRT 💫
## Introduction
miniRT is a concise and efficient ray tracing project developed as part of the 42 school's common core curriculum. This project showcases the fundamental concepts of ray tracing by rendering basic geometric shapes like spheres, cylinders, and infinite planes. It is divided into a mandatory part and an enhanced bonus part, offering a deeper dive into the complexities of computer graphics.

## Features

### Mandatory Part
- **Basic Shapes**: Render three fundamental shapes - sphere, cylinder, and infinite plane.
- **Lighting**: Implement basic lighting models including ambient lighting and brightness adjustments.
- **Camera**: Utilize a camera to view the scene from different perspectives.
- **Compilation**: Use the `all` rule in the Makefile for compilation.

### Bonus Part
- **Threading**: Improve performance by implementing multithreading.
- **Anti-Aliasing**: Achieve smoother images by randomly distributing rays around the pixel to average color values.
- **New Object - Cone**: Introduce an additional geometric shape for more complex scenes.
- **Enhanced Lighting**: Support for colored and multiple light sources.
- **Textures**: Apply a checker texture to any object for added visual detail.

## Installation

Clone the repository and compile the project:
```bash
git clone [https://github.com/hanmpark/miniRT]
cd miniRT
make all
```
For the bonus part, compile with `make bonus`

## Usage

Run the executable with a scene description file:
```bash
./miniRT [scene_file].rt
```

