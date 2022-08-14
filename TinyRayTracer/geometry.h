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

	int get_size () {
		return size;
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

	// adding a number to a vector
	Vec3f operator+(const float& v) {
		this->x = this->x + v;
		this->y = this->y + v;
		this->z = this->z + z;
		return *this;
	}

	// multipling a number to a vector
	Vec3f operator*(const float& v) {
		this->x = this->x * v;
		this->y = this->y * v;
		this->z = this->z * z;
		return *this;
	}

	// adding a vector to a vector
	Vec3f operator+(const Vec3f& v) {
		return Vec3f (this->x + v.x, this->y + v.y, this->z + v.z);
	}

	// dividing a number by a vector
	Vec3f operator/(const float& i) {
		return Vec3f (this->x / i, this->y / i, this->z / i);
	}

	// subtracing a vector by another vector


};
