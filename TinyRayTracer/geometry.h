#pragma once

class Vec3f {
private:
	float x, y, z;
public:
	Vec3f () { x = 0.0; y = 0.0; z = 0.0; };
	Vec3f (int a, int b) : x (a), y (b) { z = 0.0; }
	Vec3f (int a, int b, int c) : x (a), y (b), z (c) {}


};