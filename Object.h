#pragma once

// 실질적인 물체를 의미하는 Object클래스
class Object {
public:
	Object();
	Object(float x, float y);
	~Object();

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
	float x{ };
	float y{ };

	// 위아래 크기
	float sizeX{ };
	float sizeY{ };

	// 회전 각도
	float m_rotateAngle{ };
	unsigned int m_drawMode{ };

	// Mesh객체
	class Mesh* m_mesh{ nullptr };

public:
	virtual void Update() = 0;
	virtual void Render();
};

