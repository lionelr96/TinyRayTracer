#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"
#include "Sphere.h"

#define M_PI 3.14159265358979323846264338327950288

std::pair<float, float> intersect_ray_sphere (Vec3f& o, Vec3f& d, Sphere& s) {
	float inf = std::numeric_limits<float>::infinity ();

	float radius = s.get_radius ();
	Vec3f co = o - s.get_center ();

	float a = d.dot (d);
	float b = 2 * co.dot (d);
	float c = co.dot (co) - radius * radius;

	float discriminate = b * b - 4 * a * c;

	if (discriminate < 0) {
		return std::make_pair (inf, inf);
	}

	float t1 = (-b + std::sqrt (discriminate)) / (2 * a);
	float t2 = (-b - std::sqrt (discriminate)) / (2 * a);
	return std::make_pair (t1, t2);
}

Vec3f trace_ray (Vec3f& o, Vec3f& d, std::vector<Sphere>& s, float t_min, float t_max) {
	float closest_t = std::numeric_limits<float>::infinity ();
	Sphere closest_sphere = Sphere ();

	for (int i = 0; i < s.size (); ++i) {
		std::pair <float, float> intersection = intersect_ray_sphere (o, d, s[i]);
		if (intersection.first >= t_min && intersection.first <= t_max && intersection.first < closest_t) {
			closest_t = intersection.first;
			closest_sphere = s[i];
		}

		if (intersection.second >= t_min && intersection.second <= t_max && intersection.second < closest_t) {
			closest_t = intersection.second;
			closest_sphere = s[i];
		}
	}

	if (!closest_sphere.check_sphere ()) {
		return Vec3f (0.0, 0.0, 0.0);
	}

	return closest_sphere.get_color ();

}

void render (std::vector<Sphere>& s) {
	const int width = 1024;
	const int height = 768;
	const int fov = M_PI / 2;
	std::vector<Vec3f> framebuffer (width * height);
	Vec3f origin (0.0, 0.0, 0.0);
	float constexpr inf = std::numeric_limits<float>::infinity ();

	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < width; i++) {
			float x = (2 * (i + 0.5) / (float)width - 1) * tan (fov / 2.) * width / (float)height;
			float y = -(2 * (j + 0.5) / (float)height - 1) * tan (fov / 2.);
			Vec3f dir = Vec3f (x, y, -1).normalize ();
			framebuffer[i + j * width] = trace_ray (origin, dir, s, 1, inf);
		}
	}

	std::cout << "Framebuffer created\n";

	std::ofstream ofs; // save the framebuffer to file
	ofs.open ("./out.ppm", std::ofstream::out | std::ofstream::binary);
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
	std::vector<Sphere> spheres;
	// spheres are rendered on the order of the center, color, and radius
	spheres.push_back (Sphere (Vec3f (-5, 0, -15), Vec3f (0.8, 0, 0), 1.5)); // red
	spheres.push_back (Sphere (Vec3f (3, 0, -17), Vec3f (0, 0, 0.8), 2)); // blue
	spheres.push_back (Sphere (Vec3f (-1, 0, -14), Vec3f (0, 0.8, 0), 2)); // green
	spheres.push_back (Sphere (Vec3f (-10, 0, -20), Vec3f (1, 0, 1), 1.5)); // purple
	spheres.push_back (Sphere (Vec3f (7, 0, -20), Vec3f (1, 1, 0), 1.5)); // yellow
	spheres.push_back (Sphere (Vec3f (0, -5001, 0), Vec3f (1, 1, 0), 5000));
	render (spheres);
	return 0;
}