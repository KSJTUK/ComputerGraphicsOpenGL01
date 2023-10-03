#pragma once

#include "Object.h"
#include "constants.h"

class TEST{ };

class Triangle : public Object {
public:
	Triangle();
	~Triangle() { }

	Triangle(float x, float y, float sizeX);
	Triangle(const Vec3F& position, const Size3F& size);
	Triangle(const Vec3F& position, const Size3F& size, const Color3F& color);
	Triangle(const Vec3F& position, const Size3F& size, const Color3F* colors);
	Triangle(const Vec3F* positions, const Color3F* colors);

protected:
	Color3F m_vertexColor[3]{ { 1.f, 0.f, 0.f }, { 0.f, 1.f, 0.f }, { 0.f, 0.f, 1.f } };
	Vec3F m_originPoints[3]{ };
	Vec3F m_moveVec{ };

public:
	Vec3F GetGravityPoint(const Vec3F* vectors);
	void SetRotateAngle(float rotateAngle);
	void AddRotateAngle(float addAngle);
	void SetDrawMode(int drawMode);
	void SetColor(const Color3F& color);
	void SetColor(const Color3F& color1, const Color3F& color2, const Color3F& color3);
	void SetColor(const Color3F* color);
	void SetColorRandom();
	void SetColorRandomVertex();

	void SetMoveVec(const Vec3F& moveVec) { m_moveVec = moveVec; }
	void SetMoveSpeed(const float moveSpeed) { m_moveSpeed = moveSpeed;  }
	Vec3F GetMoveVec() { return m_moveVec; }

public:
	bool IsInBox(const Vec3F& lt, const Vec3F& rb);
	bool CheckOut(const Vec3F& minWindow, const Vec3F& maxWindow);

	bool OutX(const Vec3F& minWindow, const Vec3F& maxWindow);

	bool OutY(const Vec3F& minWindow, const Vec3F& maxWindow);

private:
	bool rateMove{ false };
	int m_moveState{ 0 };
	float timeRate{ 0.5f };
	float moveTime{ };
	Vec3F prevMoveX{ };
	Vec3F prevMoveY{ };
	Vec3F prevMoveDir{ };
	Vec3F rateMoveVec{ MoveDir::down };
	float m_moveSpeed{ 150.f };

public:
	void Move(float deltaTime);
	void MoveToState(int moveState, float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow);
	void MoveZig(float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow);
	void MovePingPong(float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow);

public:
	void Update(float deltaTime);
	void Render(class Mesh* mesh);
};

