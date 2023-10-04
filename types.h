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

	float operator[](size_t);

	Vec3F operator-(const Vec3F& rhs) const;
	Vec3F operator+(const Vec3F& rhs) const;

	void operator-=(const Vec3F& rhs);
	void operator+=(const Vec3F& rhs);

	bool operator==(const Vec3F& rhs) const;
	bool operator!=(const Vec3F& rhs) const;

	float x{ };
	float y{ };
	float z{ };
};

struct Color3F {
	Color3F() { }
	~Color3F() { }
	Color3F(float r, float g, float b) : r{ r }, g{ g }, b{ b } { }
	Color3F(const Color3F& other) : r{ other.r }, g{ other.g }, b{ other.b } { }
	Color3F& operator=(const Color3F& other);
	float operator[](size_t index) const;
	float r{ };
	float g{ };
	float b{ };
};

using Size3F = Vec3F;

struct Vertex {
	Vec3F vector;
	Color3F color;
};

Vec3F GetRandomVec3F(float minX, float minY, float maxX, float maxY);
Color3F GetRandomColor3F(float min, float max);
int GetRandomInt(int min, int max);

// 유용한 함수들 정의
void SafeDeletePointer(void* pointer);
void SafeDeleteArrayPointer(void* pointer);

int winXToGLX(int x);
int winYToGLY(int y);

bool isInBox(const Vec3F& pos, const Vec3F& lt, const Vec3F& rb);