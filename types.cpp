#include "types.h"
#include "Engine.h"
#include "pch.h"

extern Engine e;

Vec3F& Vec3F::operator=(const Vec3F& other) {
		x = other.x;
		y = other.y;
		z = other.z;
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
		x / widthF,
		y / heightF,
		z
	};
	return rtVec;
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
