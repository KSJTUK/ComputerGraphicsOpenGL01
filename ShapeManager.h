#pragma once
#include <list>
#include "Object.h"

class ShapeManager {
public:
	ShapeManager() { }
	~ShapeManager() { }

private:
	std::list<Object*> m_shapeList{ };

public:
	void CreateTriangle(float x, float y, float sizeX, float sizeY);
	void CreatePoint(float x, float y);

public:
	void Update();
	void Render();
	void Clear();
};

