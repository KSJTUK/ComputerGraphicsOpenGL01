#include "training_solution.h"
#include "pch.h"
#include "Engine.h"
#include "ShapeManager.h"

extern class Engine e;

void draw_spiral(float deltaTime)
{
	static float timeElapsed{ 0.f };

	static float radius{ 0.f };
	static float angle{ 0.f };
	float x{ };
	float y{ };

	float rad = angle * 3.141592 / 180.f;
	timeElapsed += deltaTime;
	if (timeElapsed > 0.001f) {
		timeElapsed = 0.f;
		x = (std::cosf(rad) * radius + x) / (e.GetWindowfWidth() / 2);
		y = (std::sinf(rad) * radius + y) / (e.GetWindowfHeight() / 2);
		std::cout << "x: " << x << ", y: " << y << std::endl;
		e.GetShapeManager()->CreatePoint(x, y);
		angle += 2.f;
		radius += 0.5f;
	}

}

void draw_heart(float deltaTime)
{

}