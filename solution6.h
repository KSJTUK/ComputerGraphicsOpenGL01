#pragma once

#include "Engine.h"
#include "constants.h"
#include "ShapeManager.h"
#include "Point.h"
#include "Triangle.h"
#include "types.h"
#include "pch.h"

extern Engine e;

namespace solution7 {
	Vec3F moveVec{ };
	Vec3F minWindow{ };
	Vec3F maxWindow{ };

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

		e.SubscribeDrawFunc(solution7::renderFunc);
		e.SubscribeReshapeFunc(solution7::reshapeFunc);
		e.SubscribeMouseFunc(solution7::mouseFunc);
		e.SubscribeIdleFUnc(solution7::idleFunc);
		e.SubscribeKeyboardFunc(solution7::keyboardFunc);
		e.SubscribeKeyboardUpfunc(solution7::keyboardUpFunc);

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
		e.GetShapeManager()->MoveAll(moveVec);
		glutPostRedisplay();
	}


	void keyboardFunc(unsigned char key, int x, int y)
	{
		Color3F triangleColors[3]{ };
		Color3F rectangleColors[4]{ };
		switch (key) {
		case 'w':
			moveVec += MoveDir::up;
			if (moveVec.y > 1.f) {
				moveVec.y = 1.f;
			}
			break;

		case 'a':
			moveVec += MoveDir::left;
			if (moveVec.x < -1.f) {
				moveVec.x = -1.f;
			}
			break;

		case 's':
			moveVec += MoveDir::down;
			if (moveVec.y < -1.f) {
				moveVec.y = -1.f;
			}
			break;

		case 'd':
			moveVec += MoveDir::right;
			if (moveVec.x > 1.1f) {
				moveVec.x = 1.f;
			}
			break;

		case 'p':
			if (e.GetShapeManager()->GetShapeListSize() < 10) {
				e.GetShapeManager()->CreatePoint(GetRandomVec3F(minWindow.x, minWindow.y, maxWindow.x, maxWindow.y), GetRandomColor3F(0.f, 1.f));
			}
			break;

		case 'l':
			if (e.GetShapeManager()->GetShapeListSize() < 10) {
				e.GetShapeManager()->CreateLine(GetRandomVec3F(minWindow.x, minWindow.y, maxWindow.x, maxWindow.y),
					GetRandomVec3F(minWindow.x, minWindow.y, maxWindow.x, maxWindow.y),
					GetRandomColor3F(0.f, 1.f));
			}
			break;

		case 't':
			if (e.GetShapeManager()->GetShapeListSize() < 10) {
				e.GetShapeManager()->CreateTriangle(GetRandomVec3F(minWindow.x, minWindow.y, maxWindow.x, maxWindow.y), 100, GetRandomColor3F(0.f, 1.f));
			}
			break;

		case 'r':
			if (e.GetShapeManager()->GetShapeListSize() < 10) {
				e.GetShapeManager()->CreateRectangle(GetRandomVec3F(minWindow.x, minWindow.y, maxWindow.x, maxWindow.y),
					GetRandomVec3F(100.f, 100.f, 150.f, 150.f), GetRandomColor3F(0.f, 1.f));
			}
			break;

		case 'c':
			e.GetShapeManager()->Clear();
			break;

		case '[':
			if (e.GetShapeManager()->GetShapeListSize() < 10) {
				for (int i = 0; i < 4; ++i) {
					rectangleColors[i] = GetRandomColor3F(0.f, 1.f);
				}
				e.GetShapeManager()->CreateRectangle(GetRandomVec3F(minWindow.x, minWindow.y, maxWindow.x, maxWindow.y),
					GetRandomVec3F(100.f, 100.f, 150.f, 150.f), rectangleColors);
			}
			break;

		case ']':
			if (e.GetShapeManager()->GetShapeListSize() < 10) {
				for (int i = 0; i < 3; ++i) {
					triangleColors[i] = GetRandomColor3F(0.f, 1.f);
				}
				e.GetShapeManager()->CreateTriangle(GetRandomVec3F(minWindow.x, minWindow.y, maxWindow.x, maxWindow.y), 100, triangleColors);
			}
			break;

		case 'q':
			exit(0);
			break;

		default:
			break;
		}
	}

	void keyboardUpFunc(unsigned char key, int x, int y)
	{
		switch (key) {
		case 'w':
			moveVec -= MoveDir::up;
			break;

		case 'a':
			moveVec -= MoveDir::left;
			break;

		case 's':
			moveVec -= MoveDir::down;
			break;

		case 'd':
			moveVec -= MoveDir::right;
			break;

		default:
			break;
		}
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

}