#include "Polygon.h"
#include "Mesh.h"
#include "pch.h"

PolygonF::PolygonF(const Vec3F& origin, float size, int vertexSize) : Object{  } {
	m_origin = origin;
	m_vertexSize = vertexSize % m_vertexLimit;
	m_polygonSize = size;

	if (m_vertexSize == 1) {
		m_state = POINT;
	}
	else if (m_vertexSize == 2) {
		m_state = LINE;
	}
	else {
		m_state = POLYGON;
	}

	CreatePolygonState(m_state);
	CreateIndexBuffer(m_state);
}

PolygonF::~PolygonF() {
	SafeDeleteArrayPointer(m_indexBuffer);
}

void PolygonF::CreatePoint() {
	m_indexBufferSize = POINT;
	m_vertexBufferSize = POINT * 6;
	m_drawVertexSize = POINT;
	m_drawMode = GL_POINTS;

	m_pointList.push_back(m_origin);
	m_colorList.push_back(GetRandomColor3F(0.f, 1.f));
}

void PolygonF::CreateLine() {
	m_indexBufferSize = LINE;
	m_vertexBufferSize = LINE * 6;
	m_drawVertexSize = LINE;
	m_drawMode = GL_LINES;

	Vec3F line[2]{
		{ m_origin.x - m_polygonSize / 2.f, m_origin.y, 0.f },
		{ m_origin.x + m_polygonSize / 2.f, m_origin.y, 0.f }
	};
	m_pointList.push_back(line[0]);
	m_pointList.push_back(line[1]);
	m_colorList.push_back(GetRandomColor3F(0.f, 1.f));
	m_colorList.push_back(GetRandomColor3F(0.f, 1.f));
}

void PolygonF::CreatePolygon() {
	m_indexBufferSize = m_vertexSize * 3;
	m_vertexBufferSize = (m_vertexSize + 1) * 6;
	m_drawVertexSize = m_vertexSize * 3;

	m_drawMode = GL_TRIANGLES;

	m_pointList.push_back(m_origin);

	Vec3F setPoint{ m_polygonSize, 0.f, 0.f };
	if (m_vertexSize == 4) {
		setPoint = setPoint.Rotate(45);
	}
	else {
		setPoint = setPoint.Rotate(90);
	}

	float rotateAngle = 360.f / m_vertexSize;
	for (int i = 0; i < m_vertexSize; ++i) {
		Vec3F pushPoint = setPoint;
		float angle = rotateAngle * i;
		pushPoint = pushPoint.Rotate(angle);
		pushPoint += m_origin;
		m_pointList.push_back(pushPoint);
	}

	for (int i = 0; i < m_vertexSize + 1; ++i) {
		m_colorList.push_back(GetRandomColor3F(0.f, 1.f));
	}
}

void PolygonF::CreateIndexBuffer(state st) {
	m_indexBuffer = new unsigned int[m_indexBufferSize];
	switch (st) {
	case POINT:
		m_indexBuffer[0] = 0;
		break;

	case LINE:
		for (int i = 0; i < LINE; ++i) {
			m_indexBuffer[i] = i;
		}
		break;

	case POLYGON:
		for (int i = 0; i < m_vertexSize; ++i) {
			int curIdxStart{ i * 3 };
			m_indexBuffer[curIdxStart] = 0;
			m_indexBuffer[curIdxStart + 1] = i + 1;
			m_indexBuffer[curIdxStart + 2] = i + 2;
		}
		m_indexBuffer[m_indexBufferSize - 1] = 1;
		break;
	}
	
}

float* PolygonF::PointAndLineToVBuffer() {
	float* vertexBuffer{ new float[m_vertexBufferSize] };
	auto pListIter = m_pointList.begin();
	auto cListIter = m_colorList.begin();
	for (int i = 0; i < m_vertexSize; ++i, ++pListIter, ++cListIter) {
		Vec3F vec = (*pListIter);
		Color3F color = (*cListIter);
		vec = vec.ToGLCoordinate();
		for (int v = 0; v < 3; ++v) {
			vertexBuffer[i * 6 + v] = vec[v];
		}

		for (int c = 3; c < 6; ++c) {
			vertexBuffer[i * 6 + c] = color[c % 3];
		}
	}
	return vertexBuffer;
}

float* PolygonF::PolygonToVBuffer() {
	float* vertexBuffer{ new float[(m_vertexSize + 1) * 6] };
	auto pListIter = m_pointList.begin();
	auto cListIter = m_colorList.begin();
	for (int i = 0; i < m_vertexSize + 1; ++i, ++pListIter, ++cListIter) {
		Vec3F vec = (*pListIter);
		Color3F color = (*cListIter);
		vec = vec.ToGLCoordinate();
		for (int v = 0; v < 3; ++v) {
			vertexBuffer[i * 6 + v] = vec[v];
		}

		for (int c = 3; c < 6; ++c) {
			vertexBuffer[i * 6 + c] = color[c % 3];
		}
	}
	return vertexBuffer;
}

void PolygonF::SetDrawMode(int drawMode) {
	if (m_state == POLYGON) {
		m_drawMode = drawMode;
	}
}

void PolygonF::CreatePolygonState(state st) {
	switch (st) {
	case POINT:
		CreatePoint();
		break;

	case LINE:
		CreateLine();
		break;

	case POLYGON:
		CreatePolygon();
		break;
	}
}

float* PolygonF::VectorListToVBuffer(state st) {
	float* vertexBuffer{ nullptr };
	switch (st) {
	case POLYGON:
		vertexBuffer = PolygonToVBuffer();
		break;

	default:
		vertexBuffer = PointAndLineToVBuffer();
		break;
	}
	return vertexBuffer;
}

void PolygonF::Update(float deltaTime) {
}

void PolygonF::Render(Mesh* renderer) {
	float* vertexBuffer = VectorListToVBuffer(m_state);

	renderer->SetDrawMode(m_drawMode);
	renderer->SetVertexs(vertexBuffer, m_vertexBufferSize, m_drawVertexSize);
	renderer->SetIndexBuffer(m_indexBuffer, m_indexBufferSize);
	renderer->Render();

	delete[] vertexBuffer;
}
