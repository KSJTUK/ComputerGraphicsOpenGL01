#pragma once

#include "Object.h"
#include "constants.h"
#include <list>

class PolygonF : public Object {
public:
	PolygonF(const Vec3F& origin, float size, int vertexSize);
	~PolygonF();

private:
	enum state {
		POINT = 1,
		LINE,
		POLYGON
	};

private:
	int m_vertexLimit{ 12 };

	std::list<Vec3F> m_pointList{ };
	std::list<Color3F> m_colorList{ };
	unsigned int* m_indexBuffer{ };

	float m_polygonSize{ };

	state m_state{ };

	int m_vertexBufferSize{ };
	int m_drawVertexSize{ };
	int m_indexBufferSize{ };

	Vec3F m_prevOrigin{ };

private:

	bool rateMove{ false };
	int m_moveState{ 1 };
	float timeRate{ 1.f };
	float moveTime{ };
	Vec3F prevMoveX{ };
	Vec3F prevMoveY{ };
	Vec3F prevMoveDir{ };
	Vec3F rateMoveVec{ MoveDir::down };

	float m_moveSpeed{ 150.f };
	float m_spiralMoveAngle{ };
	float m_spiralMoveRadius{ };
	float m_spiralRadiusDir{ 1.f };

	float m_moveWhileVar{ };
	Vec3F m_moveWhileSt{ };
	bool m_moveWhile{ false };

	int m_outCountX{ };
	int m_outCountY{ };
	bool m_rotated{ true };

	Vec3F m_moveVec{ };

public:
	bool OutX(const Vec3F& minWindow, const Vec3F& maxWindow);

	bool OutY(const Vec3F& minWindow, const Vec3F& maxWindow);

	void ResetSpecialMoveVariables(int moveState, const Vec3F& minWindow, const Vec3F& maxWindow);
	void Move(float deltaTime);
	void MoveToState(int moveState, float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow);
	void MoveToState(float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow);
	void MoveZig(float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow);
	void MovePingPong(float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow);

public:
	float GetSize() const { return m_polygonSize; }
	Vec3F GetOrigin() const { return m_origin; };
	void SetMoveState(int moveState) { m_moveState = moveState; }


private:
	void OriginMove();

	bool IsPointInPoint(const Vec3F& point);
	bool IsPointInLine(const Vec3F& point);
	bool IsPointInPolygon(const Vec3F& point);
	
public:
	void DeleteOrigin();
	bool IsPointIn(const Vec3F& point);
	void SetOriginPoint(const Vec3F& point);

	bool Collision(const PolygonF& other);

private:
	void CreatePoint();
	void CreateLine();
	void CreatePolygon();
	void CreateIndexBuffer(state st);

	float* PointAndLineToVBuffer();
	float* PolygonToVBuffer();

public:
	void SetDrawMode(int drawMode);
	void CreatePolygonState(state st);

public:
	float* VectorListToVBuffer(state st);
	void Update(float deltaTime);
	void Render(class Mesh* renderer);
};

