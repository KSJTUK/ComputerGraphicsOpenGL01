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

	bool ltMove{ false };
	bool trMove{ false };
	bool rpMove{ false };
	bool ppMove{ false };

	float polygonsSize{ 100.f };

	Vec3F* lineToTriangleVec{ };
	Vec3F ltMoveEndVec{ };
	Color3F lColor{ };
	unsigned int lttIdx[3]{ 2, 1, 0 };

	Vec3F* triangleToRectVec{ };
	Vec3F trMoveEndVec[2]{ };
	Color3F tColor{ };
	unsigned int rtIdx[6]{ 2, 0, 1, 2, 1, 3 };

	Vec3F* rectToPentaVec{ };
	Vec3F rpMoveEndVec[4]{ };
	Color3F rColor{ };
	unsigned int rpIdx[15]{ 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 1 };

	Vec3F* polyToPointVec{ };
	Vec3F ppMoveEndVec[5]{ };
	Color3F pColor{ };
	unsigned int ppIdx[15]{ 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 1 };

	Mesh* renderer{ };


	float* VectorArrayToVertex(Vec3F* vec, int size, Color3F& color);
	void VertexRender(Mesh* renderer, float* vertexBuf, int vertexBufSize, int vertexSize, unsigned int* idxBuf, int idxBufSize);

	void DrawAll();

	void Init();
	void ReInit();

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

		Init();

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
		float* lttVertex = VectorArrayToVertex(lineToTriangleVec, 3, lColor);
		VertexRender(renderer, lttVertex, 18, 3, lttIdx, 3);
		delete[] lttVertex;

		float* rtVertex = VectorArrayToVertex(triangleToRectVec, 4, tColor);
		VertexRender(renderer, rtVertex, 24, 6, rtIdx, 6);
		delete[] rtVertex;

		float* rpVertex = VectorArrayToVertex(rectToPentaVec, 6, rColor);
		VertexRender(renderer, rpVertex, 36, 15, rpIdx, 15);
		delete[] rpVertex;

		float* ppVertex = VectorArrayToVertex(polyToPointVec, 6, pColor);
		VertexRender(renderer, ppVertex, 36, 15, ppIdx, 15);
		delete[] ppVertex;

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
		if (ltMove) {
			lineToTriangleVec[2].MoveWhile(deltaTime, 0.05f, ltMoveEndVec);
		}

		if (trMove) {
			triangleToRectVec[2].MoveWhile(deltaTime, 0.05f, trMoveEndVec[0]);
			triangleToRectVec[3].MoveWhile(deltaTime, 0.05f, trMoveEndVec[1]);
		}

		if (rpMove) {
			for (int i = 0; i < 4; ++i) {
				rectToPentaVec[i + 2].MoveWhile(deltaTime, 0.05f, rpMoveEndVec[i]);
			}
		}

		if (ppMove) {
			for (int i = 0; i < 5; ++i) {
				polyToPointVec[i + 1].MoveWhile(deltaTime, 0.05f, ppMoveEndVec[i]);
			}
		}

		glutPostRedisplay();
	}


	void keyboardFunc(unsigned char key, int x, int y)
	{
		switch (key) {
		case 'l':
			ltMove = true;
			break;

		case 't':
			trMove = true;
			break;

		case 'r':
			rpMove = true;
			break;

		case 'p':
			ppMove = true;
			break;

		case 'a':
			ltMove = true;
			trMove = true;
			rpMove = true;
			ppMove = true;
			break;

		case 's':
			ltMove = false;
			trMove = false;
			rpMove = false;
			ppMove = false;
			break;

		case 'c':
			ltMove = false;
			trMove = false;
			rpMove = false;
			ppMove = false;
			ReInit();
			break;

		case 'q':
			e.~Engine();
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

	void DrawAll()
	{
	}

	void InitLT()
	{
		Vec3F quadrant[4]{
			Vec3F{ minWindow.x / 2.f, maxWindow.y / 2.f, 0.f },
			Vec3F{ maxWindow.x / 2.f, maxWindow.y / 2.f, 0.f },
			Vec3F{ minWindow.x / 2.f, minWindow.y / 2.f, 0.f },
			Vec3F{ maxWindow.x / 2.f, minWindow.y / 2.f, 0.f }
		};

		lineToTriangleVec = new Vec3F[3];
		lineToTriangleVec[0] = Vec3F{ quadrant[0].x - polygonsSize / 2.f, quadrant[0].y - polygonsSize / 2.f, 0.f };
		lineToTriangleVec[1] = Vec3F{ quadrant[0].x + polygonsSize / 2.f, quadrant[0].y - polygonsSize / 2.f, 0.f };
		lineToTriangleVec[2] = Vec3F{ quadrant[0].x, quadrant[0].y - polygonsSize / 2.f + 2.f, 0.f };
		ltMoveEndVec = Vec3F{ quadrant[0].x, quadrant[0].y + polygonsSize / 2.f, 0.f };
		lColor = GetRandomColor3F(0.f, 1.f);
	}

	void InitTR()
	{
		Vec3F quadrant[4]{
			Vec3F{ minWindow.x / 2.f, maxWindow.y / 2.f, 0.f },
			Vec3F{ maxWindow.x / 2.f, maxWindow.y / 2.f, 0.f },
			Vec3F{ minWindow.x / 2.f, minWindow.y / 2.f, 0.f },
			Vec3F{ maxWindow.x / 2.f, minWindow.y / 2.f, 0.f }
		};

		triangleToRectVec = new Vec3F[4];
		triangleToRectVec[0] = Vec3F{ quadrant[1].x - polygonsSize / 2.f, quadrant[1].y - polygonsSize / 2.f, 0.f };
		triangleToRectVec[1] = Vec3F{ quadrant[1].x + polygonsSize / 2.f, quadrant[1].y - polygonsSize / 2.f, 0.f };
		triangleToRectVec[2] = Vec3F{ quadrant[1].x, quadrant[1].y + polygonsSize / 2.f, 0.f };
		triangleToRectVec[3] = Vec3F{ quadrant[1].x, quadrant[1].y + polygonsSize / 2.f, 0.f };
		trMoveEndVec[0] = Vec3F{ quadrant[1].x - polygonsSize / 2.f, quadrant[1].y + polygonsSize / 2.f, 0.f };
		trMoveEndVec[1] = Vec3F{ quadrant[1].x + polygonsSize / 2.f, quadrant[1].y + polygonsSize / 2.f, 0.f };
		tColor = GetRandomColor3F(0.f, 1.f);
	}

	void InitRP()
	{
		Vec3F quadrant[4]{
			Vec3F{ minWindow.x / 2.f, maxWindow.y / 2.f, 0.f },
			Vec3F{ maxWindow.x / 2.f, maxWindow.y / 2.f, 0.f },
			Vec3F{ minWindow.x / 2.f, minWindow.y / 2.f, 0.f },
			Vec3F{ maxWindow.x / 2.f, minWindow.y / 2.f, 0.f }
		};

		rectToPentaVec = new Vec3F[6];
		rectToPentaVec[0] = Vec3F{ quadrant[2] };
		rectToPentaVec[1] = Vec3F{ quadrant[2].x, quadrant[2].y + polygonsSize / 2.f, 0.f };
		rectToPentaVec[2] = Vec3F{ quadrant[2].x - polygonsSize / 2.f, quadrant[2].y + polygonsSize / 2.f, 0.f };
		rectToPentaVec[3] = Vec3F{ quadrant[2].x - polygonsSize / 2.f, quadrant[2].y - polygonsSize / 2.f, 0.f };
		rectToPentaVec[4] = Vec3F{ quadrant[2].x + polygonsSize / 2.f, quadrant[2].y - polygonsSize / 2.f, 0.f };
		rectToPentaVec[5] = Vec3F{ quadrant[2].x + polygonsSize / 2.f, quadrant[2].y + polygonsSize / 2.f, 0.f };
		rpMoveEndVec[0] = Vec3F{ quadrant[2].x - polygonsSize / 2.f, quadrant[2].y, 0.f };
		rpMoveEndVec[1] = Vec3F{ quadrant[2].x - polygonsSize / 3.f, quadrant[2].y - polygonsSize / 2.f, 0.f };
		rpMoveEndVec[2] = Vec3F{ quadrant[2].x + polygonsSize / 3.f, quadrant[2].y - polygonsSize / 2.f, 0.f };
		rpMoveEndVec[3] = Vec3F{ quadrant[2].x + polygonsSize / 2.f, quadrant[2].y, 0.f };
		rColor = GetRandomColor3F(0.f, 1.f);
	}

	void InitPP()
	{
		Vec3F quadrant[4]{
			Vec3F{ minWindow.x / 2.f, maxWindow.y / 2.f, 0.f },
			Vec3F{ maxWindow.x / 2.f, maxWindow.y / 2.f, 0.f },
			Vec3F{ minWindow.x / 2.f, minWindow.y / 2.f, 0.f },
			Vec3F{ maxWindow.x / 2.f, minWindow.y / 2.f, 0.f }
		};

		polyToPointVec = new Vec3F[6];
		polyToPointVec[0] = Vec3F{ quadrant[3] };
		polyToPointVec[1] = Vec3F{ quadrant[3].x, quadrant[3].y + polygonsSize / 2.f, 0.f };
		polyToPointVec[2] = Vec3F{ quadrant[3].x - polygonsSize / 2.f, quadrant[3].y, 0.f };
		polyToPointVec[3] = Vec3F{ quadrant[3].x - polygonsSize / 3.f, quadrant[3].y - polygonsSize / 2.f, 0.f };
		polyToPointVec[4] = Vec3F{ quadrant[3].x + polygonsSize / 3.f, quadrant[3].y - polygonsSize / 2.f, 0.f };
		polyToPointVec[5] = Vec3F{ quadrant[3].x + polygonsSize / 2.f, quadrant[3].y, 0.f };

		float endSize = (polygonsSize / polygonsSize) * 5;
		ppMoveEndVec[0] = Vec3F{ quadrant[3].x, quadrant[3].y + endSize, 0.f };
		ppMoveEndVec[1] = Vec3F{ quadrant[3].x - endSize, quadrant[3].y + endSize, 0.f };
		ppMoveEndVec[2] = Vec3F{ quadrant[3].x - endSize, quadrant[3].y - endSize, 0.f };
		ppMoveEndVec[3] = Vec3F{ quadrant[3].x + endSize, quadrant[3].y - endSize, 0.f };
		ppMoveEndVec[4] = Vec3F{ quadrant[3].x + endSize, quadrant[3].y + endSize, 0.f };
		pColor = GetRandomColor3F(0.f, 1.f);
	}

	void Init()
	{
		InitLT();
		InitTR();
		InitRP();
		InitPP();
	}
	
	void ReInit()
	{
		delete[] lineToTriangleVec;
		delete[] triangleToRectVec;
		delete[] rectToPentaVec;
		delete[] polyToPointVec;
		/*SafeDeleteArrayPointer(lineToTriangleVec);
		SafeDeleteArrayPointer(triangleToRectVec);
		SafeDeleteArrayPointer(rectToPentaVec);
		SafeDeleteArrayPointer(polyToPointVec);*/
		Init();
	}


	float* VectorArrayToVertex(Vec3F* vec, int size, Color3F& color)
	{
		float* vertex{ new float[size * 6] };

		for (int i = 0; i < size; ++i) {
			for (int v = 0; v < 3; ++v) {
				Vec3F drawVec = vec[i].ToGLCoordinate();
				vertex[i * 6 + v] = drawVec[v];
			}

			for (int c = 3; c < 6; ++c) {
				vertex[i * 6 + c] = color[c % 3];
			}
		}

		return vertex;
	}

	void VertexRender(Mesh* renderer, float* vertexBuf, int vertexBufSize, int vertexSize, unsigned int* idxBuf, int idxBufSize)
	{
		renderer->SetDrawMode(GL_TRIANGLES);
		renderer->SetVertexs(vertexBuf, vertexBufSize, vertexSize);
		renderer->SetIndexBuffer(idxBuf, idxBufSize);
		renderer->Render();
	}
}