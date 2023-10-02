#pragma once
#include <list>
#include "Object.h"

class ShapeManager {
public:
	ShapeManager();
	~ShapeManager();

private:
	std::list<Object*> m_shapeList{ };
	std::list<Object*> m_pointList{ };
	class Mesh* m_mesh{ nullptr };

public:
	void DrawToLinesAll();
	void CreateTriangle(float x, float y, float size);
	void CreatePoint(float x, float y);

public:
	void Update(float deltaTime);
	void Render();
};

