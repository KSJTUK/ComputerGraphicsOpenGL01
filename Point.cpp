#include "Point.h"
#include "pch.h"
#include "Mesh.h"

void Point::Move(int moveDir) {
	x += m_dirSet[moveDir].x;
	y += m_dirSet[moveDir].y;
}

void Point::SetPt(float _x, float _y) {
	x = _x;
	y = _y;
}

void Point::Update() {
	m_drawMode = GL_POINTS;
	m_mesh->SetDrawMode(m_drawMode);
	float vertBuf[] = { x, y, 0.f, 1.f, 0.f, 0.f };
	unsigned int indexBuf[] = { 0 };

	m_mesh->SetVertexs(vertBuf, sizeof(vertBuf) / sizeof(float));
	m_mesh->SetIndexBuffer(indexBuf, sizeof(indexBuf) / sizeof(unsigned int));
}

void Point::Render() {
	Object::Render();
}