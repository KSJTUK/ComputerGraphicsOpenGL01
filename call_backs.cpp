﻿#include "call_backs.h"
#include "pch.h"

// 그리기 콜백함수
void renderFunc()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	// rendering function
	// Frame객체의 Rendering 함수 사용

	glutSwapBuffers();
}

void reshapeFunc(int x, int y)
{
	// wininfo.width = x;
	// 
	// wininfo.height = y;
	// wininfo.fWidth = static_cast<float>(x);
	// wininfo.fHeight = static_cast<float>(y);
	glViewport(0, 0, x, y);
}

void idleFunc()
{
	// Frame객체의 Update함수 사용
	// Game Logic Update
	// Timer Update
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
