#pragma once

#include "Engine.h"
#include "constants.h"
#include "ShapeManager.h"
#include "Point.h"
#include "Triangle.h"
#include "types.h"
#include "pch.h"

namespace solution7 {
	Engine e{ };

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

	void solution7(int* argc, char** argv) {
		e.Init(argc, argv);

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

		glutSwapBuffers();
	}

	void reshapeFunc(int x, int y)
	{
		e.SetWindowSize(x, y);

		glViewport(0, 0, x, y);
	}

	void idleFunc()
	{
		// Frame��ü�� Update�Լ� ���
		e.Update();
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

}