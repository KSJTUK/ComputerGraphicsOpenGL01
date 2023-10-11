#pragma once

#pragma once

#include "Engine.h"
#include "constants.h"
#include "ShapeManager.h"
#include "Point.h"
#include "Rectangle.h"
#include "Mesh.h"
#include "types.h"
#include "pch.h"

extern Engine e;

namespace solution13 {
	Vec3F minWindow{ };
	Vec3F maxWindow{ };
	Line* axisX{ };
	Line* axisY{ };

	Vec3F prevMouseVec{ };

	float boxSize{ 10.f };

	Mesh* renderer{ };

	Vec3F* rect{ };
	float* rectVerticies{ };
	unsigned int* rectIndicies{ };

	Vec3F* capturedVec{ nullptr };
	bool captureRect{ false };

	void Init();

	void DrawAxis();

	void IsInVec(const Vec3F& mouseVec);
	void IsInRect(const Vec3F& mouseVec);

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

		e.SubscribeDrawFunc(solution13::renderFunc);
		e.SubscribeReshapeFunc(solution13::reshapeFunc);
		e.SubscribeMouseFunc(solution13::mouseFunc);
		e.SubscribeIdleFUnc(solution13::idleFunc);
		e.SubscribeKeyboardFunc(solution13::keyboardFunc);
		e.SubscribeKeyboardUpfunc(solution13::keyboardUpFunc);
		e.SubscribeMouseMotionFunc(mouseMotion);
		e.SubscribePassiveMotionFunc(mousePassiveMotion);

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

		DrawAxis();

		for (int i = 0; i < 4; ++i) {
			Vec3F vert = rect[i].ToGLCoordinate();
			for (int v = 0; v < 3; ++v) {
				rectVerticies[i * 6 + v] = vert[v];
			}
		}

		renderer->SetDrawMode(GL_LINES);
		renderer->SetVertexs(rectVerticies, 6 * 4, 8);
		renderer->SetIndexBuffer(rectIndicies, 8);
		renderer->Render();

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
		int glX{ winXToGLX(x) };
		int glY{ winYToGLY(y) };
		switch (button) {
		case GLUT_LEFT_BUTTON:
			mouseLeftDown(state, glX, glY);
			break;
		}
	}

	void mouseLeftDown(int state, int x, int y)
	{
		Vec3F mouseVec{ static_cast<float>(x), static_cast<float>(y), 0.f };
		switch (state) {
		case GLUT_DOWN:
			IsInVec(mouseVec);
			if (!capturedVec) {
				IsInRect(mouseVec);
			}
			break;
		}
	}

	void mouseRightDown(int state, int x, int y)
	{
	}

	void mouseMotion(int x, int y)
	{
		Vec3F mouseVec{ static_cast<float>(winXToGLX(x)), static_cast<float>(winYToGLY(y)), 0.f };
		if (capturedVec) {
			(*capturedVec) = mouseVec;
		}
		else if (captureRect) {
			for (int i = 0; i < 4; ++i) {
				Vec3F moveVec = mouseVec - prevMouseVec;
				rect[i] += moveVec;
			}
		}
		prevMouseVec = mouseVec;
	}

	void mousePassiveMotion(int x, int y)
	{
		Vec3F mouseVec{ static_cast<float>(winXToGLX(x)), static_cast<float>(winYToGLY(y)), 0.f };
		captureRect = false;
		capturedVec = nullptr;
		prevMouseVec = mouseVec;
	}

	void mouseWheel(int dir, int x, int y)
	{
	}

	void Init()
	{
		rect = new Vec3F[4]{
			Vec3F{ maxWindow.x / 2.f, maxWindow.y / 2.f, 0.f },
			Vec3F{ minWindow.x / 2.f, maxWindow.y / 2.f, 0.f },
			Vec3F{ minWindow.x / 2.f, minWindow.y / 2.f, 0.f },
			Vec3F{ maxWindow.x / 2.f, minWindow.y / 2.f, 0.f }
		};
		rectVerticies = new float[6 * 4];
		for (int i = 0; i < 4; ++i) {
			Color3F color = GetRandomColor3F(0.f, 1.f);
			for (int v = 0; v < 3; ++v) {
				rectVerticies[i * 6 + v] = rect[i][v];
			}
			for (int c = 3; c < 6; ++c) {
				rectVerticies[i * 6 + c] = color[c % 3];
			}
		}

		rectIndicies = new unsigned int[8] { 0, 1, 1, 2, 2, 3, 3, 0 };

		axisX = new Line(Vec3F{ minWindow.x, 0.f, 0.f }, Vec3F{ maxWindow.x, 0.f, 0.f }, Colors::blue);
		axisY = new Line(Vec3F{ 0.f, minWindow.y, 0.f }, Vec3F{ 0.f, maxWindow.y, 0.f }, Colors::green);
	}

	void DrawAxis()
	{
		axisX->Render(renderer);
		axisY->Render(renderer);
	}

	void IsInVec(const Vec3F& mouseVec)
    {
		for (int i = 0; i < 4; ++i) {
			Vec3F p = rect[i];
			if (isInBox(mouseVec, Vec3F{ p.x - boxSize, p.y + boxSize, p.z }, Vec3F{ p.x + boxSize, p.y - boxSize, p.z })) {
				capturedVec = &rect[i];
				break;
			}
		}
	}

	void IsInRect(const Vec3F& mouseVec)
	{
		if (isInBox(mouseVec, rect[1], rect[3])) {
			captureRect = true;
		}
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