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
		magnitude = std::sqrt ((x * x) + (y * y) + (z * z));
	}

	float get_magnitude () {
		return magnitude;
	}

	// dot product implementation
	float dot (const Vec3f& v) {
		return this->x * v.x + this->y * v.y + this->z * v.z;
	}

	// normalizing a vector
	Vec3f normalize () {
		this->x = this->x / magnitude;
		this->y = this->y / magnitude;
		this->z = this->z / magnitude;
		return *this;
	}

	// adding subscript support
	float& operator[](int i) {
		assert (i < size);
		return i <= 0 ? x : (1 == i ? y : z);
	}

	// subtracting a vector from a vector
	Vec3f operator-(const Vec3f& v) {
		return Vec3f (this->x - v.x, this->y - v.y, this->z - v.z);
	}

	// negating a vector
	Vec3f operator-() {
		return Vec3f (this->x * -1, this->y * -1, this->z * -1);
	}

	// multipling a number to a vector
	Vec3f operator*(const float& v) {
		return Vec3f (this->x * v, this->y * v, this->z * v);
	}

	// adding a vector to a vector
	Vec3f operator+(const Vec3f& v) {
		return Vec3f (this->x + v.x, this->y + v.y, this->z + v.z);
	}

	// dividing a number by a vector
	Vec3f operator/(const float& i) {
		return Vec3f (this->x / i, this->y / i, this->z / i);
	}

	// cross product
	Vec3f operator*(const Vec3f& v) {
		int x_value = this->y * v.z - this->z * v.y;
		int y_value = this->x * v.z - this->z * v.x;
		int z_value = this->x * v.y - this->y * v.x;
		return Vec3f (x_value, y_value, z_value);
	}

};
