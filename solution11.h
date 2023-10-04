#pragma once

#include "Engine.h"
#include "constants.h"
#include "ShapeManager.h"
#include "Point.h"
#include "Mesh.h"
#include "Triangle.h"
#include "Polygon.h"
#include "types.h"
#include "pch.h"
#include <vector>

extern Engine e;

namespace solution11 {
	Vec3F minWindow{ };
	Vec3F maxWindow{ };

	Mesh* renderer{ };
	PolygonF* polygon{ };


	void DrawAll();

	void Init();

	// 그리기 콜백함수
	void renderFunc();

	// 윈도우 사이즈 변경 처리 함수
	void reshapeFunc(int, int);

	// idle time 함수
	void idleFunc();

	// 키보드 입력처리 함수
	void keyboardFunc(unsigned char, int, int);
	void keyboardUpFunc(unsigned char, int, int);

	// 키보드 특수키 처리함수
	void specialkeyFunc(int, int, int);

	// 마우스 입력 처리함수
	void mouseFunc(int, int, int, int);
	void mouseLeftDown(int, int, int);
	void mouseRightDown(int, int, int);

	// 마우스 모션함수
	void mouseMotion(int, int);
	void mousePassiveMotion(int, int);

	// 마우스 휠 입력함수
	void mouseWheel(int, int, int);

	void solution(int* argc, char** argv) {
		e.Init(argc, argv);

		float width = e.GetWindowWidthF();
		float height = e.GetWindowHeightF();
		minWindow = { -width / 2.f, -height / 2.f, 0.f };
		maxWindow = { width / 2.f, height / 2.f, 0.f };

		renderer = e.GetShapeManager()->GetMesh();
		polygon = new PolygonF{ Vec3F{ 0.f, 0.f, 0.f }, 100.f, 1 };

		e.SubscribeDrawFunc(solution11::renderFunc);
		e.SubscribeReshapeFunc(solution11::reshapeFunc);
		e.SubscribeMouseFunc(solution11::mouseFunc);
		e.SubscribeIdleFUnc(solution11::idleFunc);
		e.SubscribeKeyboardFunc(solution11::keyboardFunc);
		e.SubscribeKeyboardUpfunc(solution11::keyboardUpFunc);

		e.Loop();
	}

	// 그리기 콜백함수
	void renderFunc()
	{
		Color3F bgColor{ Colors::gray };
		glClearColor(bgColor.r, bgColor.b, bgColor.b, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// rendering function
		e.Render();
		polygon->Render(renderer);

		glutSwapBuffers();
	}

	void reshapeFunc(int x, int y)
	{
		e.SetWindowSize(x, y);

		float width = e.GetWindowWidthF();
		float height = e.GetWindowHeightF();
		minWindow = { -width / 2.f, -height / 2.f, 0.f };
		maxWindow = { width / 2.f, height / 2.f, 0.f };

		glViewport(0, 0, x, y);
	}

	void idleFunc()
	{
		// Frame객체의 Update함수 사용
		e.Update();
		float deltaTime = e.GetDeltaTime();

		glutPostRedisplay();
	}


	void keyboardFunc(unsigned char key, int x, int y)
	{

	}

	void keyboardUpFunc(unsigned char key, int x, int y)
	{

	}

	void specialkeyFunc(int key, int x, int y)
	{
	}

	void mouseFunc(int button, int state, int x, int y)
	{
	}

	void mouseLeftDown(int state, int x, int y)
	{
	}

	void mouseRightDown(int state, int x, int y)
	{
	}

	void mouseMotion(int x, int y)
	{
	}

	void mousePassiveMotion(int x, int y)
	{
	}

	void mouseWheel(int dir, int x, int y)
	{
	}

	void Init()
	{
		
	}

	void DrawAll()
	{
	}

}