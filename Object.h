#pragma once

#include "types.h"
#include <string>

// 실질적인 물체를 의미하는 Object클래스
class Object {
public:
	Object();
	virtual ~Object();

	Object(float x, float y, float z, float sizeX, float sizeY, float sizeZ);
	Object(const Vec3F& position, const Size3F& size);

	struct DIR {
		int x{ };
		int y{ };
	};

	enum DIR_NUM {
		LEFT,
		LEFT_UP,
		UP,
		RIGHT_UP,
		RIGHT,
		RIGHT_DOWN,
		DOWN,
		LEFT_DOWN,
		DIR_NULL,
	};

	DIR m_dirSet[9]{
		{ -1, 0 },
		{ -1, 1 },
		{ 0, 1 },
		{ 1, 1 },
		{ 1, 0 },
		{ 1, -1 },
		{ 0, -1 },
		{ -1, -1 },
		{ 0, 0 }
	};

protected:
	// 중심점 x, y
	Vec3F m_origin{ 0.f, 0.f, 0.f };

	// 위아래 크기
	Size3F m_size{ 0.f, 0.f, 0.f };

	// 회전 각도
	float m_rotateAngle{ };
	unsigned int m_drawMode{ };

	std::string m_tag{ };

public:
	std::string GetObjectTag() const { return m_tag; }

public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render(class Mesh* mesh) = 0;
};

