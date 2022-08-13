#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void render () {
	const int width = 1024;
	const int height = 768;
	std::vector<Vec3f> framebuffer (width * height);

	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < width; i++) {
			framebuffer[i + j * width] = Vec3f (j / float (height), i / float (width), 0);
		}
	}

	std::cout << "Framebuffer created\n";

	std::ofstream ofs; // save the framebuffer to file
	ofs.open ("./out_3.ppm", std::ofstream::out | std::ofstream::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (size_t i = 0; i < height * width; ++i) {
		for (size_t j = 0; j < 3; j++) {
			ofs << (char)(255 * std::max (0.f, std::min (1.f, framebuffer[i][j])));
		}
	}
	ofs.close ();
	std::cout << "Image created!" << std::endl;

}

int main () {
	render ();
	return 0;
}