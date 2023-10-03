#pragma once

#include "constants.h"
#include "Object.h"

class Line : public Object {
public:
	Line(const Vec3F& v1, const Vec3F& v2);
	Line(const Vec3F& v1, const Vec3F& v2, const Color3F& color);
	Line(const Vec3F& v1, const Vec3F& v2, const Color3F* colors);
	~Line() { }

private:
	Vec3F m_start{ };
	Vec3F m_end{ };
	Color3F m_vertexColor[2]{ Colors::red, Colors::blue };


public:
	void SetStartEndPoint(const Vec3F& start, const Vec3F& end);

	void SetRotateAngle(float rotateAngle);
	void AddRotateAngle(float addAngle);
	void SetDrawMode(int dtawMode) { };

public:
	void Update(float deltaTime);
	void Render(class Mesh* mesh);
};

