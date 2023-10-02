#pragma once

#include "Object.h"

class Triangle : public Object {
public:
	Triangle();
	~Triangle() { }

	Triangle(float x, float y, float sizeX);
	Triangle(const Vec3F& position, const Size3F& size);
	Triangle(const Vec3F* positions, const Color3F* colors, int indexSize);

private:
	Color3F m_vertexColor[3]{ { 1.f, 0.f, 0.f }, { 0.f, 1.f, 0.f }, { 0.f, 0.f, 1.f } };
	Vec3F m_originPoints[3]{ };

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

public:
	void Update(float deltaTime);
	void Render(class Mesh* mesh);
};

