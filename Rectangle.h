#pragma once

#include "Object.h"
#include "constants.h"

class RectF : public Object {
public:
	RectF(const Vec3F& origin, const Size3F& size);
	~RectF() { }

private:
	Vec3F m_originPoints[4]{ };
	Color3F m_vertexColor[4]{ Colors::red, Colors::blue, Colors::green, Colors::red };

public:

	void SetRotateAngle(float rotateAngle);
	void AddRotateAngle(float addAngle);
	void SetDrawMode(int drawMode);
	void SetColor(const Color3F& color);
	void SetColor(const Color3F& color1, const Color3F& color2, const Color3F& color3, const Color3F& color4);
	void SetColor(const Color3F* color);
	void SetColorRandom();
	void SetColorRandomVertex();

public:
	void Update(float deltaTime);
	void Render(class Mesh* mesh);
};

