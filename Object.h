﻿#pragma once

#include "types.h"
#include <string>

// 실질적인 물체를 의미하는 Object클래스
class Object {
public:
	Object();
	virtual ~Object();

	Object(float x, float y, float z, float sizeX, float sizeY, float sizeZ);
	Object(const Vec3F& position, const Size3F& size);
	Object(const Object& other);

protected:
	// 중심점 x, y
	Vec3F m_origin{ 0.f, 0.f, 0.f };

	// 위아래 크기
	Size3F m_size{ 0.f, 0.f, 0.f };

	// 회전 각도
	float m_rotateAngle{ };
	unsigned int m_drawMode{ };
	float m_moveSpeed{ 10.f };
	int m_vertexSize{ };

	std::string m_tag{ };

public:
	std::string GetObjectTag() const { return m_tag; }
	int GetVertexSize() const { return m_vertexSize; }

	void SetMoveSpeed(float speed);
	void SetOriginPoint(const Vec3F& setPt);

	virtual void SetDrawMode(int drawMode) = 0;

public:
	void Move(const Vec3F& moveDir);
	void Move(const Vec3F& moveDir, float deltaTime, float speed);
	virtual void Update(float deltaTime) = 0;
	virtual void Render(class Mesh* mesh) = 0;
};

