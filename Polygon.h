#pragma once

#include "Object.h"
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
	int m_vertexLimit{ 21 };
	std::list<Vec3F> m_pointList{ };
	std::list<Color3F> m_colorList{ };
	unsigned int* m_indexBuffer{ };

	float m_polygonSize{ };

	state m_state{ };

	int m_vertexBufferSize{ };
	int m_drawVertexSize{ };
	int m_indexBufferSize{ };

private:
	void CreatePoint();
	void CreateLine();
	void CreatePolygon();
	void CreateIndexBuffer(state st);

	float* PointAndLineToVBuffer();
	float* PolygonToVBuffer();

public:
	void SetPt(const Vec3F& pt);
	void SetDrawMode(int drawMode);
	void CreatePolygonState(state st);

public:
	float* VectorListToVBuffer(state st);
	void Update(float deltaTime);
	void Render(class Mesh* renderer);
};

