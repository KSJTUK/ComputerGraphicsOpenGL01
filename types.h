#pragma once

struct Vec3F {
	Vec3F() { }
	~Vec3F() { }
	Vec3F(float x, float y, float z) : x{ x }, y{ y }, z{ z } { }
	Vec3F(const Vec3F& other) : x{ other.x }, y{ other.y }, z{ other.z } { }
	Vec3F& operator=(const Vec3F& other);

	Vec3F Rotate(float rotateAngle);
	Vec3F Move(const Vec3F& moveVec);
	Vec3F ToGLCoordinate();

	Vec3F operator-(const Vec3F& rhs) const;
	Vec3F operator+(const Vec3F& rhs) const;

	float x{ };
	float y{ };
	float z{ };
};

struct Color3F {
	float r;
	float g;
	float b;
};

using Size3F = Vec3F;

struct Vertex {
	Vec3F vector;
	Color3F color;
};

Vec3F GetRandomVec3F(float minX, float minY, float maxX, float maxY);
Color3F GetRandomColor3F(float min, float max);