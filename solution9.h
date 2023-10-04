#pragma once

#include "Engine.h"
#include "constants.h"
#include "ShapeManager.h"
#include "Line.h"
#include "Point.h"
#include "Spiral.h"
#include "Triangle.h"
#include "types.h"
#include "pch.h"
#include <list>

extern Engine e;

namespace solution9 {
	Vec3F minWindow{ };
	Vec3F maxWindow{ };
	Mesh* renderer{ };
	std::list<Triangle*> triangleList{ };
	Spiral* s{ };

	// �׸��� �ݹ��Լ�
	void renderFunc();

	// ������ ������ ���� ó�� �Լ�
	void reshapeFunc(int, int);

	// idle time �Լ�
	void idleFunc();

	// Ű���� �Է�ó�� �Լ�
	void keyboardFunc(unsigned char, int, int);
	void keyboardUpFunc(unsigned char, int, int);

	// Ű���� Ư��Ű ó���Լ�
	void specialkeyFunc(int, int, int);

	// ���콺 �Է� ó���Լ�
	void mouseFunc(int, int, int, int);
	void mouseLeftDown(int, int, int);
	void mouseRightDown(int, int, int);

	// ���콺 ����Լ�
	void mouseMotion(int, int);
	void mousePassiveMotion(int, int);

	// ���콺 �� �Է��Լ�
	void mouseWheel(int, int, int);

	// �̵��Լ�
	void MoveToState(Triangle* triangle, int moveState, float deltaTime);

	void solution(int* argc, char** argv) {
		e.Init(argc, argv);

		float width = e.GetWindowWidthF();
		float height = e.GetWindowHeightF();
		minWindow = { -width / 2.f, -height / 2.f, 0.f };
		maxWindow = { width / 2.f, height / 2.f, 0.f };

		e.SubscribeDrawFunc(solution9::renderFunc);
		e.SubscribeReshapeFunc(solution9::reshapeFunc);
		e.SubscribeMouseFunc(solution9::mouseFunc);
		e.SubscribeIdleFUnc(solution9::idleFunc);
		e.SubscribeKeyboardFunc(solution9::keyboardFunc);
		e.SubscribeKeyboardUpfunc(solution9::keyboardUpFunc);

		renderer = e.GetShapeManager()->GetMesh();

		triangleList.push_back(new Triangle{ Vec3F{ }, GetRandomVec3F(100.f, 0.f, 100.f, 0.f), Colors::red });
		s = new Spiral{ Vec3F{ }, 60, 2 };

		e.Loop();
	}

	// �׸��� �ݹ��Լ�
	void renderFunc()
	{
		Color3F bgColor{ Colors::gray };
		glClearColor(bgColor.r, bgColor.b, bgColor.b, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// rendering function
		e.Render();
		s->Render(renderer);
		for (auto& e : triangleList) {
			e->Render(renderer);
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

		glViewport(0, 0, x, y);
	}

	void idleFunc()
	{
		// Frame��ü�� Update�Լ� ���
		e.Update();
		float deltaTime = e.GetDeltaTime();
		for (auto& e : triangleList) {
			MoveToState(e, 3, deltaTime);
		}
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
	
	void MoveToState(Triangle* triangle, int moveState, float deltaTime)
	{
		triangle->MoveToState(moveState, deltaTime, minWindow, maxWindow);
	}
}