#include "Point.h"
#include "pch.h"
#include "Mesh.h"

void Point::SetRotateAngle(float rotateAngle) {
	m_rotateAngle = rotateAngle;
}

void Point::AddRotateAngle(float addAngle) {
	m_rotateAngle += addAngle;
}

void Point::SetPt(float _x, float _y) {
	m_origin.x = _x;
	m_origin.y = _y;
}

void Point::Update(float deltaTime) {
	m_drawMode = GL_POINTS;
}

void Point::SetDrawMode(int drawMode) {
}

void Point::SetColor(const Color3F& color) {
	m_color = color;
}

void Point::Render(Mesh* mesh) {
	mesh->SetDrawMode(m_drawMode);

	Vec3F drawVec = m_origin.Rotate(m_rotateAngle);
	drawVec = drawVec.ToGLCoordinate();

	float vertBuf[] = { drawVec.x, drawVec.y, drawVec.z, m_color.r, m_color.g, m_color.b };
	unsigned int indexBuf[] = { 0 };

	mesh->SetVertexs(vertBuf, sizeof(vertBuf) / sizeof(float), 1);
	mesh->SetIndexBuffer(indexBuf, sizeof(indexBuf) / sizeof(unsigned int));
	mesh->Render();
}
