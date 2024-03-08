# miniRT 💫
## Introduction
The core objective is to create a program capable of rendering 3D scenes by simulating the way light interacts with objects, using ray tracing techniques. This method offers a deep understanding of fundamental graphics concepts such as lighting models, shadows, reflections, and more, providing a solid foundation in both the theory and application of computer graphics.

Here is an example of what our miniRT can do:
![miniRT](https://github.com/hanmpark/miniraytracer/blob/master/minirt_bonus.png)

## Features

### Mandatory Part
- **Basic Shapes**: Render three fundamental shapes - sphere, cylinder, and infinite plane.
- **Lighting**: Implement basic lighting models including ambient lighting and brightness adjustments.
- **Camera**: Utilize a camera to view the scene from different perspectives.

### Bonus Part
- **Threading**: Improve performance by implementing multithreading.
- **Anti-Aliasing**: Achieve smoother images by randomly distributing rays around the pixel to average color values.
- **New Object - Cone**: Introduce an additional geometric shape for more complex scenes.
- **Enhanced Lighting**: Support for colored and multiple light sources.
- **Textures**: Apply a checker texture to any object for added visual detail.

## Project Impact
This project not only demystifies the process behind generating photorealistic images but also sharpens problem-solving and software engineering skills. It challenges students to apply complex mathematical concepts and optimize algorithms for performance, preparing them for future endeavors in computer graphics and beyond.

## Installation

Clone the repository and compile the project:
```bash
git clone https://github.com/hanmpark/miniRT
cd miniRT
make all
```
For the bonus part, compile with `make bonus`

## Usage

Run the executable with a scene description file:
```bash
./miniRT [scene_file.rt]
```

