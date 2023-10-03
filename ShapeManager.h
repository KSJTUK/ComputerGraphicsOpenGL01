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
	void MoveAll(const Vec3F& moveVec);
	void DrawToLinesAll();
	void CreateTriangle(float x, float y, float size);
	void CreateTriangle(const Vec3F& origin, float size);
	void CreateTriangle(const Vec3F& origin, float size, const Color3F& color);
	void CreateTriangle(const Vec3F& origin, float size, const Color3F* colors);
	void CreatePoint(float x, float y);
	void CreatePoint(const Vec3F& origin);
	void CreatePoint(const Vec3F& origin, const Color3F& color);
	void CreateRectangle(const Vec3F& origin, const Size3F& size);
	void CreateRectangle(const Vec3F& origin, const Size3F& size, const Color3F& color);
	void CreateRectangle(const Vec3F& origin, const Size3F& size, const Color3F* colors);

	void Clear();

public:
	size_t GetShapeListSize() const { return m_shapeList.size(); }

public:
	void Update(float deltaTime);
	void Render();
};

