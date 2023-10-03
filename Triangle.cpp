#include "Triangle.h"
#include "Mesh.h"
#include "pch.h"

Triangle::Triangle() : Object{ } {
	m_tag = "Triangle";
	m_drawMode = GL_TRIANGLES;
}

Triangle::Triangle(float x, float y, float size) : Object{ x, y, 0.f, size, 0.f, 0.f } {
	m_originPoints[0] = { 0.f, m_size.x * 2.f / 3.f, 0.f };
	m_originPoints[1] = { -m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	m_originPoints[2] = { m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	m_tag = "Triangle";
	m_drawMode = GL_TRIANGLES;
}

Triangle::Triangle(const Vec3F& position, const Size3F& size) : Object{ position, size } {
	m_originPoints[0] = { 0.f, m_size.x * 2.f / 3.f, 0.f };
	m_originPoints[1] = { -m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	m_originPoints[2] = { m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	m_tag = "Triangle";
	m_drawMode = GL_TRIANGLES;
}

Triangle::Triangle(const Vec3F& position, const Size3F& size, const Color3F& color) : Object{ position, size } {
	m_originPoints[0] = { 0.f, m_size.x * 2.f / 3.f, 0.f };
	m_originPoints[1] = { -m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	m_originPoints[2] = { m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	for (int i = 0; i < 3; ++i) {
		m_vertexColor[i] = color;
	}
	m_tag = "Triangle";
	m_drawMode = GL_TRIANGLES;
}

Triangle::Triangle(const Vec3F& position, const Size3F& size, const Color3F* colors) : Object{ position, size } {
	m_originPoints[0] = { 0.f, m_size.x * 2.f / 3.f, 0.f };
	m_originPoints[1] = { -m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	m_originPoints[2] = { m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	for (int i = 0; i < 3; ++i) {
		m_vertexColor[i] = colors[i];
	}
	m_tag = "Triangle";
	m_drawMode = GL_TRIANGLES;
}

Triangle::Triangle(const Vec3F* positions, const Color3F* colors) {
	m_origin = GetGravityPoint(positions);
	for (int i = 0; i < 3; ++i) {
		m_originPoints[i] = positions[i] - m_origin;
		m_vertexColor[i] = colors[i];
	}
	m_tag = "Triangle";
	m_drawMode = GL_TRIANGLES;
}

Vec3F Triangle::GetGravityPoint(const Vec3F* vectors) {
	Vec3F rtVec{ };
	for (int i = 0; i < 3; ++i) {
		rtVec.x += vectors[i].x;
		rtVec.y += vectors[i].y;
	}
	rtVec.x /= 3.f;
	rtVec.y /= 3.f;
	return rtVec;
}

void Triangle::SetRotateAngle(float rotateAngle) {
	m_rotateAngle = rotateAngle;
}

void Triangle::AddRotateAngle(float addAngle) {
	m_rotateAngle += addAngle;
}

void Triangle::SetDrawMode(int drawMode) {
	m_drawMode = drawMode;
}

void Triangle::SetColor(const Color3F& color) {
	for (int i = 0; i < 3; ++i) {
		m_vertexColor[i] = color;
	}
}

void Triangle::SetColor(const Color3F& color1, const Color3F& color2, const Color3F& color3) {
	m_vertexColor[0] = color1;
	m_vertexColor[1] = color2;
	m_vertexColor[2] = color3;
}

void Triangle::SetColor(const Color3F* color) {
	for (int i = 0; i < 3; ++i) {
		m_vertexColor[i] = color[i];
	}
}

void Triangle::SetColorRandom() {
	Color3F randColor = GetRandomColor3F(0.f, 1.f);
	for (int i = 0; i < 3; ++i) {
		m_vertexColor[i] = randColor;
	}
}

void Triangle::SetColorRandomVertex() {
	for (int i = 0; i < 3; ++i) {
		m_vertexColor[i] = GetRandomColor3F(0.f, 1.f);
	}
}

void Triangle::Update(float deltaTime) {
	
}

void Triangle::Render(Mesh* mesh) {
	mesh->SetDrawMode(m_drawMode); 

	Vec3F drawVec[3]{ };
	for (int i = 0; i < 3; ++i) {
		drawVec[i] = m_originPoints[i].Rotate(m_rotateAngle);
		drawVec[i] = drawVec[i] + m_origin;
		drawVec[i] = drawVec[i].ToGLCoordinate();
	}

	float vertBuf[]{
		drawVec[0].x, drawVec[0].y, drawVec[0].z, m_vertexColor[0].r, m_vertexColor[0].g, m_vertexColor[0].b,
		drawVec[1].x, drawVec[1].y, drawVec[1].z, m_vertexColor[1].r, m_vertexColor[1].g, m_vertexColor[1].b,
		drawVec[2].x, drawVec[2].y, drawVec[2].z, m_vertexColor[2].r, m_vertexColor[2].g, m_vertexColor[2].b,
	};
	unsigned int indexBuf[]{ 0, 1, 2 };

	mesh->SetVertexs(vertBuf, sizeof(vertBuf) / sizeof(float), 3);
	mesh->SetIndexBuffer(indexBuf, sizeof(indexBuf) / sizeof(unsigned int));
	mesh->Render();
}
