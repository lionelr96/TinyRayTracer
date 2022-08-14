#pragma once

#include <string>
#include "geometry.h"

class Light {
private:
	std::string type;
	float intensity;
	Vec3f position, direction;

public:
	Light (std::string t, float i) : type (t), intensity (i) {
		position = Vec3f (0.0, 0.0, 0.0);
		direction = Vec3f (0.0, 0.0, 0.0);
	}
	Light (std::string t, float i, Vec3f pos) : type (t), intensity (i) {
		if (t == "point") {
			position = pos;
			direction = Vec3f (0.0, 0.0, 0.0);
		}
		else {
			direction = pos;
			position = Vec3f (0.0, 0.0, 0.0);
		}
	}

	std::string get_type () {
		return type;
	}

	float get_intensity () {
		return intensity;
	}

	Vec3f get_position () {
		return position;
	}

	Vec3f get_direction () {
		return direction;
	}
};