#pragma once

#include "Engine.h"
#include "constants.h"
#include "ShapeManager.h"
#include "Line.h"
#include "Point.h"
#include "Triangle.h"
#include "types.h"
#include "pch.h"
#include <list>

extern Engine e;

namespace solution8 {
	Vec3F minWindow{ };
	Vec3F maxWindow{ };
	Line* axisX{ };
	Line* axisY{ };
	std::list<Triangle*> triangleList{ };
	Mesh* renderer{ };
	bool drawLineMode{ };


	void Init();

	void RenderAxis();

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


		e.SubscribeDrawFunc(solution8::renderFunc);
		e.SubscribeReshapeFunc(solution8::reshapeFunc);
		e.SubscribeMouseFunc(solution8::mouseFunc);
		e.SubscribeIdleFUnc(solution8::idleFunc);
		e.SubscribeKeyboardFunc(solution8::keyboardFunc);
		e.SubscribeKeyboardUpfunc(solution8::keyboardUpFunc);

		Init();

		e.Loop();
	}

	void Init()
	{
		renderer = e.GetShapeManager()->GetMesh();
		axisX = new Line(Vec3F{ minWindow.x, 0.f, 0.f }, Vec3F{ maxWindow.x, 0.f, 0.f }, Colors::black);
		axisY = new Line(Vec3F{ 0.f, minWindow.y, 0.f }, Vec3F{ 0.f, maxWindow.y, 0.f }, Colors::black);

		triangleList.push_back(new Triangle{ Vec3F{ maxWindow.x / 2.f, maxWindow.y / 2.f, 0.f }, GetRandomVec3F(100.f, 0.f, 200.f, 0.f), GetRandomColor3F(0.f, 1.f) });
		triangleList.push_back(new Triangle{ Vec3F{ minWindow.x / 2.f, maxWindow.y / 2.f, 0.f }, GetRandomVec3F(100.f, 0.f, 200.f, 0.f), GetRandomColor3F(0.f, 1.f) });
		triangleList.push_back(new Triangle{ Vec3F{ minWindow.x / 2.f, minWindow.y / 2.f, 0.f }, GetRandomVec3F(100.f, 0.f, 200.f, 0.f), GetRandomColor3F(0.f, 1.f) });
		triangleList.push_back(new Triangle{ Vec3F{ maxWindow.x / 2.f, minWindow.y / 2.f, 0.f }, GetRandomVec3F(100.f, 0.f, 200.f, 0.f), GetRandomColor3F(0.f, 1.f) });
	}

	// 축 그리기 함수
	void RenderAxis()
	{
		axisX->Render(renderer);
		axisY->Render(renderer);
	}

	// 그리기 콜백함수
	void renderFunc()
	{
		Color3F bgColor{ Colors::gray };
		glClearColor(bgColor.r, bgColor.b, bgColor.b, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// rendering function
		e.Render();
		RenderAxis();
		for (auto& t : triangleList) {
			t->Render(renderer);
		}

		glutSwapBuffers();
	}

	void reshapeFunc(int x, int y)
	{
		e.SetWindowSize(x, y);

		float width = e.GetWindowWidthF();
		float height = e.GetWindowHeightF();
		minWindow = { -width / 2.f, -height / 2.f, 0.f };
		maxWindow = { width / 2.f, height / 2.f, 0.f };

		axisX->SetStartEndPoint(Vec3F{ minWindow.x, 0.f, 0.f }, Vec3F{ maxWindow.x, 0.f, 0.f });
		axisY->SetStartEndPoint(Vec3F{ 0.f, minWindow.y, 0.f }, Vec3F{ 0.f, maxWindow.y, 0.f });

		glViewport(0, 0, x, y);
	}

	void idleFunc()
	{
		// Frame객체의 Update함수 사용
		e.Update();
		if (drawLineMode) {
			for (auto& e : triangleList) {
				e->SetDrawMode(GL_LINE_LOOP);
			}
		}
		else {
			for (auto& e : triangleList) {
				e->SetDrawMode(GL_TRIANGLES);
			}
		}

		glutPostRedisplay();
	}


	void keyboardFunc(unsigned char key, int x, int y)
	{
		switch (key) {
		case 'a':
			drawLineMode = false;
			break;

		case 'b':
			drawLineMode = true;
			break;

		case 'q':
			exit(0);
			break;
		}
	}

	void keyboardUpFunc(unsigned char key, int x, int y)
	{

	}

	void specialkeyFunc(int key, int x, int y)
	{
	}

	void mouseFunc(int button, int state, int x, int y)
	{
		int glX{ winXToGLX(x) }, glY{ winYToGLY(y) };
		switch (button) {
		case GLUT_LEFT_BUTTON:
			mouseLeftDown(state, glX, glY);
			break;

		default:
			break;
		}

		glutPostRedisplay();
	}

	void DeleteTriangleInList(const Vec3F& lt, const Vec3F& rb) 
	{
		auto iter = triangleList.begin();
		auto iterEnd = triangleList.end();
		for (; iter != iterEnd; ) {
			if ((*iter)->IsInBox(lt, rb)) {
				SafeDeletePointer((*iter));
				iter = triangleList.erase(iter);
			}
			else {
				++iter;
			}
		}
	}

	void mouseLeftDown(int state, int x, int y)
	{
		Vec3F quadrant[4][2]{
			{ { 0.f, maxWindow.y, 0.f }, {maxWindow.x, 0.f, 0.f}},
			{ { minWindow.x, maxWindow.y, 0.f  }, { 0.f, 0.f, 0.f } },
			{ { minWindow.x, 0.f, 0.f }, { 0.f, minWindow.y, 0.f } },
			{ { 0.f, 0.f, 0.f }, { maxWindow.x, minWindow.y, 0.f } }
		};
		Vec3F mouseVec{ static_cast<float>(x), static_cast<float>(y), 0.f };
		Vec3F select[2]{ };
		switch (state) {
		case GLUT_DOWN:
			for (int i = 0; i < 4; ++i) {
				if (isInBox(mouseVec, quadrant[i][0], quadrant[i][1])) {
					select[0] = quadrant[i][0];
					select[1] = quadrant[i][1];
				}
			}
			DeleteTriangleInList(select[0], select[1]);
			triangleList.push_back(new Triangle(mouseVec, GetRandomVec3F(100.f, 0.f, 200.f, 0.f), GetRandomColor3F(0.f, 1.f)));
			break;
		}
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

}