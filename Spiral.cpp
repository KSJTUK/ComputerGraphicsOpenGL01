#include "Spiral.h"
#include "ShapeManager.h"
#include "constants.h"
#include "Mesh.h"
#include "Engine.h"
#include "pch.h"

extern Engine e;

Spiral::Spiral(const Vec3F& origin, size_t numOfPoint, float radiusStep, int revRad, int revAngle) : m_numOfPoints{ numOfPoint }, m_endDraw{ numOfPoint } {
	m_drawMode = GL_LINE_STRIP;
	m_origin = origin;
	m_prevOrigin = { };
	Color3F color{ Colors::white };

	if (m_numOfPoints % 2 == 1) {
		m_startDraw = m_numOfPoints / 2;
		m_endDraw = m_numOfPoints / 2 + 1;
	}
	else {
		m_startDraw = m_numOfPoints / 2;
		m_endDraw = m_numOfPoints / 2;
	}
	
	m_vertexBuffer = new float[m_numOfPoints * 6] { };
	m_radius = 0.f;
	m_angle = 0.f;

	if (revRad) {
		m_radiusDir = -1.f;
	}

	if (revAngle) {
		m_angleDir = -1.f;
	}

	Vec3F point{ };
	Vec3F pointOrigin{ };
	for (int i = 0; i < m_numOfPoints; ++i) {
		float radianAngle = m_angle * Constant::f_Pi / 180.f;
		point.x = (pointOrigin.x + (m_angleDir * std::cosf(radianAngle) * m_radius));
		point.y = (pointOrigin.y + (m_angleDir * std::sinf(radianAngle) * m_radius));

		if (i == m_numOfPoints / 2) {
			pointOrigin = { point.x * 2, point.y * 2, 0.f };
			m_radiusDir = -m_radiusDir;
			m_angleDir = -m_angleDir;
			m_angle = 0.f;
		}

		point = point.ToGLCoordinate();

		for (int v = 0; v < 3; ++v) {
			m_vertexBuffer[i * 6 + v] = point[v];
		}
		for (int c = 3; c < 6; ++c) {
			m_vertexBuffer[i * 6 + c] = color[c % 3];
		}

		m_radius += radiusStep * m_radiusDir;
		m_angle += (360.f / m_numOfPoints * 4) * m_angleDir;
	}

	pointOrigin = pointOrigin.ToGLCoordinate();
	for (int i = 0; i < m_numOfPoints; ++i) {
		for (int v = 0; v < 3; ++v) {
			m_vertexBuffer[i * 6 + v]  -= pointOrigin[v] / 2.f;
		}
	}
}

Spiral::~Spiral() {
}

void Spiral::Init() {

}

void Spiral::SetColor(const Color3F& color) {
	float* vertexBuffer = new float[m_numOfPoints * 6];
	for (int i = 0; i < m_numOfPoints; ++i) {
		for (int c = 3; c < 6; ++c) {
			m_vertexBuffer[i * 6 + c] = color[c % 3];
		}
	}
}

void Spiral::SetColorRandom() {
	for (int i = 0; i < m_numOfPoints; ++i) {
		for (int c = 3; c < 6; ++c) {
			Color3F color = GetRandomColor3F(0.f, 1.f);
			m_vertexBuffer[i * 6 + c] = color[c % 3];
		}
	}
}

void Spiral::DrawPoint() {
	m_drawMode = GL_POINTS;
}

void Spiral::DrawLine() {
	m_drawMode = GL_LINE_STRIP;
}

void Spiral::Update(float deltaTime) {
	if (m_prevOrigin != m_origin) {
		Vec3F origin = m_origin.ToGLCoordinate();
		for (int i = 0; i < m_numOfPoints; ++i) {
			for (int v = 0; v < 3; ++v) {
				m_vertexBuffer[i * 6 + v] += origin[v];
			}
		}
		m_origin = m_prevOrigin;
	}

	m_timeCount += deltaTime;
	if (m_draw) {
		if (m_timeRateDraw < m_timeCount) {
			m_timeCount = 0.f;
			m_startDraw -= 1;
			m_endDraw += 1;
			if (m_startDraw == 0 or m_endDraw == m_numOfPoints) {
				m_draw = false;
				m_delete = true;
			}
		}
	}
	else {
		if (m_timeRateDelete < m_timeCount) {
			m_timeCount = 0.f;
			m_startDraw += 1;
			m_endDraw -= 1;
			if (m_startDraw == m_numOfPoints / 2) {
				m_draw = true;
				m_delete = false;
			}
		}
	}
}

void Spiral::Render(Mesh* mesh) {
	mesh->SetDrawMode(m_drawMode);
	mesh->SetVertexs(m_vertexBuffer, m_numOfPoints * 6, m_endDraw - m_startDraw);
	unsigned int* indexBuf = new unsigned int[(m_endDraw - m_startDraw)];
		for (int i = m_startDraw; i < m_endDraw; ++i) {
			indexBuf[i - m_startDraw] = i;
		}
	mesh->SetIndexBuffer(indexBuf, m_endDraw - m_startDraw);
	mesh->Render();
	delete[] indexBuf;
}
