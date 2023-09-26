#include "call_backs.h"
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

void keyboardFunc(unsigned char, int, int, int)
{
}

void specialkeyFunc(int, int, int)
{
}

void mouseFunc(int, int, int, int)
{
}

void mouseLeftDown(int, int, int)
{
}

void mouseRightDown(int, int, int)
{
}

void mouseMotion(int, int)
{
}

void mousePassiveMotion(int, int)
{
}

void mouseWheel(int, int, int)
{
}
