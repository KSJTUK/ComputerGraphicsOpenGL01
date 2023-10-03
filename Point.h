#pragma once
#include "Object.h"

class Point : public Object {
public:
	Point() : Object{ } { m_tag = { "Point" }; }
	~Point() { }

	Point(float x, float y, float z) : Object{ x, y, z, 0.f, 0.f, 0.f } { m_tag = { "Point" }; }
	Point(const Vec3F& position) : Object{ position, Size3F{ 0.f, 0.f, 0.f } } { m_tag = { "Point" }; }

private:
	Color3F m_color{ 1.f, 0.f, 0.f };

public:
	void SetRotateAngle(float rotateAngle);
	void AddRotateAngle(float addAngle);
	void SetPt(float x, float y);
	void SetDrawMode(int drawMode);

public:
	bool CheckOut() { return false; }
	void Update(float deltaTime) override;
	void Render(class Mesh* mesh) override;
};

