# TinyRayTracer

This is an incredibly simple ray tracer only capable of rendering 3D images. At this time it will only be able to render spheres. The ray tracing algorithm used is the original Whitted algorithm first published in 1979 in the paper "An improved illumination model for shaded display". This is a simplistic implementation of that algorithm using only ray-sphere intersection. Eventually I may add other features and maybe other sorts of intersections if I have the time or interest.

Currently the renderer is capable of rendering shadows, reflectance, along with fancy looking specular and diffuse lighting. So far it only produces a PPM image of the rendered scene with no support for real-time rendering. At this time the project is only for educational purposes. It draws code from various graphics tutorial books and websites to make the code as easy to understand as possible. I mainly want it to help other people get their start in understanding the very basics of ray tracing using C++.

## Building
Building is quite easy. Just run the main.cpp file and your compiler should do the rest. You can change the file name to output the specific file. You can add spheres or other light sources to create any effect you want.

