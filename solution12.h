#pragma once

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
#include <list>

extern Engine e;

namespace solution12 {
	Vec3F minWindow{ };
	Vec3F maxWindow{ };

	Mesh* renderer{ };
	std::list<PolygonF*> polygons{ };
	PolygonF* capturedPolygon{ };

	Vec3F prevMouseVec{ };

	void DrawAll();

	void Init();

	void polyCollision(PolygonF* poly);

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

	void solution(int* argc, char** argv) {
		e.Init(argc, argv);

		float width = e.GetWindowWidthF();
		float height = e.GetWindowHeightF();
		minWindow = { -width / 2.f, -height / 2.f, 0.f };
		maxWindow = { width / 2.f, height / 2.f, 0.f };

		renderer = e.GetShapeManager()->GetMesh();
		
		for (int i = 0; i < 12; ++i) {
			Vec3F randomVec{ GetRandomVec3F(minWindow.x + 100.f, minWindow.y + 100.f, maxWindow.x - 100.f, maxWindow.y - 100.f) };
			float randomSize{ GetRandomF(40.f, 120.f) };
			int randomVSize = GetRandomInt(1, 20);
			int randMoveState = GetRandomInt(0, 100);
			polygons.push_back(new PolygonF{ randomVec, randomSize, randomVSize });
			polygons.back()->SetMoveState(randMoveState % 2 + 1);
			polygons.back()->ResetSpecialMoveVariables(randMoveState, minWindow, maxWindow);
		}

		e.SubscribeDrawFunc(solution12::renderFunc);
		e.SubscribeReshapeFunc(solution12::reshapeFunc);
		e.SubscribeMouseFunc(solution12::mouseFunc);
		e.SubscribeIdleFUnc(solution12::idleFunc);
		e.SubscribeKeyboardFunc(solution12::keyboardFunc);
		e.SubscribeKeyboardUpfunc(solution12::keyboardUpFunc);
		e.SubscribeMouseMotionFunc(mouseMotion);
		e.SubscribePassiveMotionFunc(mousePassiveMotion);

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
		for (auto& polygon : polygons) {
			polygon->Render(renderer);
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
		for (auto& polygon : polygons) {
			if ((void*)(polygon) != capturedPolygon) {
				polygon->MoveToState(deltaTime, minWindow, maxWindow);
			}
			polygon->Update(deltaTime);
		}

		polyCollision(capturedPolygon);

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
			for (auto& polygon : polygons) {
				if (polygon->IsPointIn(mouseVec)) {
					capturedPolygon = polygon;
					break;
				}
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
		if (capturedPolygon) {
			Vec3F setPt = capturedPolygon->GetOrigin();
			setPt += mouseVec - prevMouseVec;
			capturedPolygon->SetOriginPoint(setPt);
		}
		prevMouseVec = mouseVec;
	}

	void mousePassiveMotion(int x, int y)
	{
		Vec3F mouseVec{ static_cast<float>(winXToGLX(x)), static_cast<float>(winYToGLY(y)), 0.f };
		capturedPolygon = nullptr;
		prevMouseVec = mouseVec;
	}

	void mouseWheel(int dir, int x, int y)
	{
	}

	void Init()
	{

	}

	void DrawAll()
	{
	}

	void polyCollision(PolygonF* poly)
	{
		if (poly == nullptr) {
			return;
		}

		auto iter = polygons.begin();
		auto iterEnd = polygons.end();
		for (; iter != iterEnd;) {
			if ((void*)(*iter) == (void*)poly) {
				++iter;
				continue;
			}

			if (poly->Collision(*(*iter))) {
				Vec3F polyVec = poly->GetOrigin();
				float polySize = poly->GetSize();
				int vSize1 = (*iter)->GetVertexSize();
				int vSize2 = poly->GetVertexSize();

				SafeDeletePointer(*iter);
				polygons.erase(iter);

				iter = polygons.begin();
				while ((void*)(*iter) != (void*)poly) { ++iter; }
				SafeDeletePointer(*iter);
				polygons.erase(iter);

				PolygonF* newPoly = new PolygonF{ polyVec, polySize, vSize1 + vSize2 };
				polygons.push_back(newPoly);
				capturedPolygon = newPoly;
				break;
			}
			else {
				++iter;
			}
		}
	}

}