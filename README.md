
Simple Graphics Library (SGL)
=============================

A simple library for learning and experimenting with Graphics APIs, written in C++.
For now, supports only OpenGL 4.5.

## Features:

* Abstractions of OpenGL objects for easy use under RAII concept,
* Window abstraction using GLFW3,
* Application base class for quick and clean prototyping.
* Logging abstraction

## Used Libraries:

* window abstraction: [GLFW3](https://github.com/glfw/glfw)
* OpenGL headers: [GLAD](https://glad.dav1d.de/)
* logging library: [SPDLOG](https://github.com/gabime/spdlog)
* math library: [GLM](https://github.com/g-truc/glm)

## How to Use

See examples/ directory.

Use '--recursive' when cloning.

- style used: [Google C++ Style](https://google.github.io/styleguide/cppguide.html)

## License

Distributed under MIT License Copyright (c) 2022 authors
