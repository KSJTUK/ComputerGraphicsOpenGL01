#include "Line.h"
#include "Mesh.h"
#include "pch.h"

Line::Line(const Vec3F& v1, const Vec3F& v2) {
	m_origin = { (v1.x + v2.x) / 2.f, (v1.y + v2.y) / 2.f, 0.f };
	m_start = v1 - m_origin;
	m_end = v2 - m_origin;
	m_tag = "Line";
	m_drawMode = GL_LINES;
}

Line::Line(const Vec3F& v1, const Vec3F& v2, const Color3F& color) {
	m_origin = { (v1.x + v2.x) / 2.f, (v1.y + v2.y) / 2.f, 0.f };
	m_start = v1 - m_origin;
	m_end = v2 - m_origin;
	for (int i = 0; i < 2; ++i) {
		m_vertexColor[i] = color;
	}
	
	m_tag = "Line";
	m_drawMode = GL_LINES;
}

Line::Line(const Vec3F& v1, const Vec3F& v2, const Color3F* colors) {
	m_origin = { (v1.x + v2.x) / 2.f, (v1.y + v2.y) / 2.f, 0.f };
	m_start = v1 - m_origin;
	m_end = v2 - m_origin;
	for (int i = 0; i < 2; ++i) {
		m_vertexColor[i] = colors[i];
	}

	m_tag = "Line";
	m_drawMode = GL_LINES;
}

void Line::SetStartEndPoint(const Vec3F& start, const Vec3F& end) {
	m_origin = { (start.x + end.x) / 2.f, (start.y + end.y) / 2.f, 0.f };
	m_start = start - m_origin;
	m_end = end - m_origin;
}

void Line::SetRotateAngle(float rotateAngle) {
	m_rotateAngle = rotateAngle;
}

void Line::AddRotateAngle(float addAngle) {
	m_rotateAngle += addAngle;
}

void Line::Update(float deltaTime) {
}

void Line::Render(Mesh* mesh) {
	mesh->SetDrawMode(m_drawMode);

	Vec3F drawVec[2]{ m_start, m_end };
	for (int i = 0; i < 2; ++i) {
		drawVec[i] = drawVec[i].Rotate(m_rotateAngle);
		drawVec[i] = drawVec[i] + m_origin;
		drawVec[i] = drawVec[i].ToGLCoordinate();
	}

	float vertBuf[]{
		drawVec[0].x, drawVec[0].y, drawVec[0].z, m_vertexColor[0].r, m_vertexColor[0].g, m_vertexColor[0].b,
		drawVec[1].x, drawVec[1].y, drawVec[1].z, m_vertexColor[1].r, m_vertexColor[1].g, m_vertexColor[1].b,
	};
	unsigned int indexBuf[]{ 0, 1 };

	mesh->SetVertexs(vertBuf, sizeof(vertBuf) / sizeof(float), 2);
	mesh->SetIndexBuffer(indexBuf, sizeof(indexBuf) / sizeof(unsigned int));
	mesh->Render();
}
