#include "Engine.h"
#include "ShapeManager.h"
#include "constants.h"
#include "pch.h"
#include "call_backs.h"
#include "Shader.h"

extern class Engine e;
Vec3F moveVec{ };

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
