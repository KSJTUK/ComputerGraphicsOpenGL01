#pragma once

#include "types.h"
#include "Point.h"
#include <list>

class Spiral {
public:
	Spiral(const Vec3F& origin, size_t numOfPoint, float radiusStep, int revRad = 0, int revAngle = 0);
	~Spiral();

	void Init();

private:
	size_t m_numOfPoints{ };

	Vec3F m_origin{ };
	Vec3F m_prevOrigin{ };

	Vec3F* m_points{ };

	float* m_vertexBuffer{ };

	float m_radius{ };
	float m_angle{ };
	
	float m_timeCount{ };
	float m_timeRateDraw{ 0.1f };
	float m_timeRateDelete{ 0.1f };

	float m_radiusDir{ 1.f };
	float m_angleDir{ 1.f };

	bool m_draw{ true };
	bool m_delete{ false };

	size_t m_startDraw{ };
	size_t m_endDraw{ };

	int m_drawMode{ };
	float m_colorTimeRate{ 0.15f };
	float m_colorTimeCount{ };

public:
	void SetColor(const Color3F& color);
	void SetColorRandom();
	void SetColorRandom(float deltaTime);
	void DrawPoint();
	void DrawLine();

public:
	void Update(float deltaTime);
	void Render(class Mesh* renderer);

};

