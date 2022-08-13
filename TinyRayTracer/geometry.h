#pragma once
#include <assert.h>
#include <cmath>

class Vec3f {
private:
	float x, y, z, magnitude;
	int size{ 3 };
public:
	Vec3f () {
		x = 0.0;
		y = 0.0;
		z = 0.0;
		magnitude = 0.0;
	}
	Vec3f (float a, float b, float c) : x (a), y (b), z (c) {
		magnitude = std::sqrt (x * x + y * y + z * z);
	}

	float& operator[](int i) {
		assert (i < size);
		return i <= 0 ? x : (1 == i ? y : z);
	}

};

