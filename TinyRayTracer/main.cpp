#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"
#include "Sphere.h"
#include "Light.h"

#define M_PI 3.14159265358979323846264338327950288

// mathematics for ray-sphere intersection
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

// lighting calculations
float compute_lighting (Vec3f& p, Vec3f& n, std::vector<Light> lights) {
	float intensity{ 0.0 };
	Vec3f l;
	for (int i = 0; i < lights.size (); ++i) {
		if (lights[i].get_type () == "ambient") {
			intensity += lights[i].get_intensity ();
		}
		else {
			if (lights[i].get_type () == "point") {
				l = lights[i].get_position () - p;
			}
			else {
				l = lights[i].get_direction ();
			}
			float n_dot_l = n.dot (l);
			if (n_dot_l > 0) {
				intensity += lights[i].get_intensity () * n_dot_l / (n.get_magnitude () * l.get_magnitude ());
			}
		}
	}
	return intensity;
}

// creates a ray from the origin and returns a color to the pixel
Vec3f trace_ray (Vec3f& origin, Vec3f& dir, std::vector<Sphere>& spheres, std::vector<Light> lights, float t_min, float t_max) {
	float closest_t = std::numeric_limits<float>::infinity ();
	Sphere closest_sphere = Sphere ();

	// determine which sphere is closest to the origin
	for (int i = 0; i < spheres.size (); ++i) {
		std::pair <float, float> intersection = intersect_ray_sphere (origin, dir, spheres[i]);
		if (intersection.first >= t_min && intersection.first < t_max && intersection.first < closest_t) {
			closest_t = intersection.first;
			closest_sphere = spheres[i];
		}

		if (intersection.second >= t_min && intersection.second < t_max && intersection.second < closest_t) {
			closest_t = intersection.second;
			closest_sphere = spheres[i];
		}
	}

	if (!closest_sphere.check_sphere ()) {
		return Vec3f (0.0, 0.0, 0.0); // background color
	}

	Vec3f point = origin + (dir * closest_t);
	Vec3f normal = point - closest_sphere.get_center ();
	normal = normal / normal.get_magnitude ();
	return closest_sphere.get_color () * compute_lighting (point, normal, lights); // final pixel color
}

// main render function
void render (std::vector<Sphere>& spheres, std::vector<Light>& lights) {
	const int width = 1024;
	const int height = 768;
	const int fov = M_PI / 2;
	std::vector<Vec3f> framebuffer (width * height);
	Vec3f origin (0.0, 3.0, 0.0);
	float constexpr inf = std::numeric_limits<float>::infinity ();

	// creating pixel colors and storing them
	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < width; i++) {
			float x = (2 * (i + 0.5) / (float)width - 1) * tan (fov / 2.) * width / (float)height;
			float y = -(2 * (j + 0.5) / (float)height - 1) * tan (fov / 2.);
			Vec3f dir = Vec3f (x, y, -1).normalize ();
			framebuffer[i + j * width] = trace_ray (origin, dir, spheres, lights, 1, inf);
		}
	}

	std::cout << "Framebuffer created\n";

	// outputting ppm
	std::ofstream ofs; // save the framebuffer to file
	ofs.open ("./out_2.ppm", std::ofstream::out | std::ofstream::binary);
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

	// lights are rendered on the order of the type, the intensity, and the position
	std::vector<Light> lights;
	lights.push_back (Light ("ambient", 0.2));
	lights.push_back (Light ("point", 0.6, Vec3f (2, 5, 0)));
	lights.push_back (Light ("directional", 0.2, Vec3f (1, 4, 4)));

	render (spheres, lights);
	return 0;
}