#include "types.h"
#include "Engine.h"
#include "pch.h"
#include "constants.h"

extern Engine e;

Vec3F& Vec3F::operator=(const Vec3F& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	moveStartX = x;
	moveStartY = y;
	return *this;
}

Vec3F Vec3F::Rotate(float rotateAngle) {
	float radianAngle{ rotateAngle * 3.141592f / 180.f };
	Vec3F rtVec{
		x * cosf(radianAngle) - y * sinf(radianAngle),
		x * sinf(radianAngle) + y * cosf(radianAngle),
		z
	};
	return rtVec;
}

Vec3F Vec3F::Move(const Vec3F& moveVec) {
	Vec3F rtVec{
		x + moveVec.x,
		y + moveVec.y,
		z + moveVec.z
	};
	return rtVec;
}

Vec3F Vec3F::ToGLCoordinate() {
	float widthF{ e.GetWindowWidthF() };
	float heightF{ e.GetWindowHeightF() };
	Vec3F rtVec{
		x / (widthF / 2.f),
		y / (heightF / 2.f),
		z
	};
	return rtVec;
}

void Vec3F::SetMoveStart(Vec3F& moveStart) {
	moveStartX = moveStart.x;
	moveStartY = moveStart.y;
}

void Vec3F::MoveWhile(float deltaTime, float timeRate, const Vec3F& end) {
	timeCount += deltaTime;
	if (t <= 1.f) {
		if (timeRate < timeCount) {
			timeCount = 0.f;
			x = (1 - t) * (moveStartX) + (t * end.x);
			y = (1 - t) * (moveStartY) + (t * end.y);
			t += 0.01;
		}
	}
	else {
		moveStartX = end.x;
		moveStartY = end.y;
		x = end.x;
		y = end.y;
		t = 0.f;
	}
}

float Vec3F::operator[](size_t index)
{
	if (index == 0) {
		return x;
	}
	else if (index == 1) {
		return y;
	}
	else {
		return z;
	}
}

Vec3F Vec3F::operator-(const Vec3F& rhs) const {
	Vec3F rtVec{
		x - rhs.x,
		y - rhs.y,
		z - rhs.z
	};
	return rtVec;
}

Vec3F Vec3F::operator+(const Vec3F& rhs) const {
	Vec3F rtVec{
		x + rhs.x,
		y + rhs.y,
		z + rhs.z
	};
	return rtVec;
}

void Vec3F::operator-=(const Vec3F& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
}

void Vec3F::operator+=(const Vec3F& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
}

bool Vec3F::operator==(const Vec3F& rhs) const {
	if (x == rhs.x and y == rhs.y and z == rhs.z) {
		return true;
	}
	return false;
}

bool Vec3F::operator!=(const Vec3F& rhs) const {
	if (x != rhs.x or y != rhs.y or z != rhs.z) {
		return true;
	}
	return false;
}

Vec3F GetRandomVec3F(float minX, float minY, float maxX, float maxY) {
	std::uniform_real_distribution<float> urdX{ minX, maxX };
	std::uniform_real_distribution<float> urdY{ minY, maxY };
	return Vec3F{ urdX(Random::dre), urdY(Random::dre), 0.f };
}

Color3F GetRandomColor3F(float min, float max) {
	std::uniform_real_distribution<float> urd{ min, max };
	return Color3F{ urd(Random::dre), urd(Random::dre), urd(Random::dre) };
}

int GetRandomInt(int min, int max) 
{
	std::uniform_int_distribution<> uid{ min, max };
	return uid(Random::dre);
}

void SafeDeletePointer(void* pointer)
{
	if (pointer) delete pointer;
	pointer = nullptr;
}

void SafeDeleteArrayPointer(void* pointer)
{
	if (pointer) delete[] pointer;
	pointer = nullptr;
}

int winXToGLX(int x)
{
	return x - ((int)e.GetWindowWidth() / 2);
}

int winYToGLY(int y)
{
	return -(y - ((int)e.GetWindowHeight() / 2));
}

bool isInBox(const Vec3F& pos, const Vec3F& lt, const Vec3F& rb)
{
	if (pos.x < rb.x and pos.x > lt.x and pos.y < lt.y and pos.y > rb.y) {
		return true;
	}
	return false;
}

Color3F& Color3F::operator=(const Color3F& other) {
	r = other.r;
	g = other.g;
	b = other.b;
	return *this;
}

float Color3F::operator[](size_t index) const {
	if (index == 0) {
		return r;
	}
	else if (index == 1) {
		return g;
	}
	else {
		return b;
	}
}

int crossOp(const Vec3F& v1, const Vec3F& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

