#pragma once

#include "geometry.h"

class Sphere {
private:
	Vec3f center, color;
	float radius, specular;
	bool is_real;

public:
	Sphere () { radius = 0.0; center = Vec3f (0.0, 0.0, 0.0); color = Vec3f (0.0, 0.0, 0.0); is_real = false; }
	Sphere (Vec3f cen, Vec3f col, float r, float s) : center (cen), color (col), radius (r), specular (s) { is_real = true; };

	float get_radius () {
		return radius;
	}

	float get_specular () {
		return specular;
	}

	// checking if sphere is real
	bool check_sphere () {
		return is_real;
	}

	Vec3f get_center () {
		return center;
	}

	Vec3f get_color () {
		return color;
	}

};