#pragma once

#include "Engine.h"
#include "constants.h"
#include "ShapeManager.h"
#include "Point.h"
#include "Mesh.h"
#include "Spiral.h"
#include "Triangle.h"
#include "types.h"
#include "pch.h"
#include <list>

extern Engine e;

namespace solution10 {
	Color3F bgColor{ Colors::gray };
	Vec3F minWindow{ };
	Vec3F maxWindow{ };
	Mesh* renderer{ };
	std::list<Spiral*> spiralList{ };
	Spiral* spirals{ };
	int moveState{ };

	void ClearSpiralList()
	{
		for (auto& e : spiralList) {
			SafeDeletePointer(e);
		}
		spiralList.clear();
	}


	void CreateSpiral(int loopSize) 
	{
		ClearSpiralList();
		bgColor = GetRandomColor3F(0.f, 1.f);

		for (int i = 0; i < loopSize; ++i) {
			spiralList.push_back(new Spiral{ GetRandomVec3F(minWindow.x + 100.f, minWindow.y + 100.f, maxWindow.x - 100.f, maxWindow.y - 100.f),
				static_cast<size_t>(GetRandomInt(1, 11) * 20), 2.f, GetRandomInt(0, 1), GetRandomInt(0, 1) });
			spiralList.back()->SetColorRandom();
		}
	}

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

		glLineWidth(3.f);

		e.SubscribeDrawFunc(solution10::renderFunc);
		e.SubscribeReshapeFunc(solution10::reshapeFunc);
		e.SubscribeMouseFunc(solution10::mouseFunc);
		e.SubscribeIdleFUnc(solution10::idleFunc);
		e.SubscribeKeyboardFunc(solution10::keyboardFunc);
		e.SubscribeKeyboardUpfunc(solution10::keyboardUpFunc);

		renderer = e.GetShapeManager()->GetMesh();

		e.Loop();
	}

	// �׸��� �ݹ��Լ�
	void renderFunc()
	{
		glClearColor(bgColor.r, bgColor.b, bgColor.b, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// rendering function
		e.Render();
		for (auto& e : spiralList) {
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
		for (auto& e : spiralList) {
			e->Update(deltaTime);
		}
		

		glutPostRedisplay();
	}


	void keyboardFunc(unsigned char key, int x, int y)
	{
		

		int loopSize{ };
		switch (key) {
		case '1':
			loopSize = 1;
			CreateSpiral(loopSize);
			break;

		case '2':
			loopSize = 2;
			CreateSpiral(loopSize);
			break;

		case '3':
			loopSize = 3;
			CreateSpiral(loopSize);
			break;

		case '4':
			loopSize = 4;
			CreateSpiral(loopSize);
			break;

		case '5':
			loopSize = 5;
			CreateSpiral(loopSize);
			break;

		case 'p':
			for (auto& s : spiralList) {
				s->DrawPoint();
			}
			break;

		case 'l':
			for (auto& s : spiralList) {
				s->DrawLine();
			}
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