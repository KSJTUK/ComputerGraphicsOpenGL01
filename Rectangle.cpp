#include "Rectangle.h"
#include "Mesh.h"
#include "pch.h"

RectF::RectF(const Vec3F& origin, const Size3F& size) : Object{ origin, size } {
	m_originPoints[0] = { -m_size.x / 2, m_size.y / 2, 0.f };
	m_originPoints[1] = { -m_size.x / 2.f, -m_size.y / 2.f, 0.f };
	m_originPoints[2] = { m_size.x / 2.f, -m_size.y / 2.f, 0.f };
	m_originPoints[3] = { m_size.x / 2.f, m_size.y / 2.f, 0.f };
	m_tag = "Rectangle";
	m_drawMode = GL_TRIANGLES;
}

RectF::RectF(const Vec3F& origin, const Size3F& size, const Color3F& color) : Object{ origin, size } {
	m_originPoints[0] = { -m_size.x / 2, m_size.y / 2, 0.f };
	m_originPoints[1] = { -m_size.x / 2.f, -m_size.y / 2.f, 0.f };
	m_originPoints[2] = { m_size.x / 2.f, -m_size.y / 2.f, 0.f };
	m_originPoints[3] = { m_size.x / 2.f, m_size.y / 2.f, 0.f };
	for (int i = 0; i < 4; ++i) {
		m_vertexColor[i] = color;
	}
	m_tag = "Rectangle";
	m_drawMode = GL_TRIANGLES;
}

RectF::RectF(const Vec3F& origin, const Size3F& size, const Color3F* colors) : Object{ origin, size } {
	m_originPoints[0] = { -m_size.x / 2, m_size.y / 2, 0.f };
	m_originPoints[1] = { -m_size.x / 2.f, -m_size.y / 2.f, 0.f };
	m_originPoints[2] = { m_size.x / 2.f, -m_size.y / 2.f, 0.f };
	m_originPoints[3] = { m_size.x / 2.f, m_size.y / 2.f, 0.f };
	for (int i = 0; i < 4; ++i) {
		m_vertexColor[i] = colors[i];
	}
	m_tag = "Rectangle";
	m_drawMode = GL_TRIANGLES;
}

void RectF::SetRotateAngle(float rotateAngle) {
	m_rotateAngle = rotateAngle;
}

void RectF::AddRotateAngle(float addAngle) {
	m_rotateAngle += addAngle;
}

void RectF::SetDrawMode(int drawMode) {
	m_drawMode = drawMode;
}

void RectF::SetColor(const Color3F& color) {
	for (int i = 0; i < 4; ++i) {
		m_vertexColor[i] = color;
	}
}

void RectF::SetColor(const Color3F* color) {
	for (int i = 0; i < 4; ++i) {
		m_vertexColor[i] = color[i];
	}
}

void RectF::SetColorRandom() {
	Color3F color = GetRandomColor3F(0.f, 1.f);
	for (int i = 0; i < 4; ++i) {
		m_vertexColor[i] = color;
	}
}

void RectF::SetColorRandomVertex() {
	for (int i = 0; i < 4; ++i) {
		m_vertexColor[i] = GetRandomColor3F(0.f, 1.f);
	}
}

void RectF::Update(float deltaTime) {
}

void RectF::Render(Mesh* mesh) {
	mesh->SetDrawMode(m_drawMode);

	Vec3F drawVec[4]{ };
	for (int i = 0; i < 4; ++i) {
		drawVec[i] = m_originPoints[i].Rotate(m_rotateAngle);
		drawVec[i] = drawVec[i] + m_origin;
		drawVec[i] = drawVec[i].ToGLCoordinate();
	}

	float vertBuf[]{
		drawVec[0].x, drawVec[0].y, drawVec[0].z, m_vertexColor[0].r, m_vertexColor[0].g, m_vertexColor[0].b,
		drawVec[1].x, drawVec[1].y, drawVec[1].z, m_vertexColor[1].r, m_vertexColor[1].g, m_vertexColor[1].b,
		drawVec[2].x, drawVec[2].y, drawVec[2].z, m_vertexColor[2].r, m_vertexColor[2].g, m_vertexColor[2].b,
		drawVec[3].x, drawVec[3].y, drawVec[3].z, m_vertexColor[2].r, m_vertexColor[2].g, m_vertexColor[2].b,
	};
	unsigned int indexBuf[]{ 
		0, 1, 2,
		0, 2, 3
	};

	mesh->SetVertexs(vertBuf, sizeof(vertBuf) / sizeof(float), 6);
	mesh->SetIndexBuffer(indexBuf, sizeof(indexBuf) / sizeof(unsigned int));
	mesh->Render();
	
}
