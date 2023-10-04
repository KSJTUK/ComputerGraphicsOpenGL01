#pragma once

#include "types.h"
#include "Point.h"
#include <list>

class Spiral {
public:
	Spiral(const Vec3F& origin, size_t numOfPoint, size_t angleStep);
	~Spiral();

	void Init();

private:
	size_t m_numOfPoints{ };

	Vec3F m_origin{ };

	Vec3F* m_points{ };

	float* m_vertexBuffer{ };

	float m_radius{ };
	float m_angle{ };
	
	float m_timeCount{ };
	float m_timeRateDraw{ 1.f };
	float m_timeRateDelete{ };

	float m_radiusDir{ 1.f };
	float m_angleDir{ 1.f };

	size_t m_startDraw{ };
	size_t m_endDraw{ };

	int m_drawMode{ };

public:
	void SetColor(const Color3F& color);
	void SetColorRandom();

public:
	void Update(float deltaTime);
	void Render(class Mesh* renderer);

};

