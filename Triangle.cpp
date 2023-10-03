#include "Triangle.h"
#include "Mesh.h"
#include "pch.h"

Triangle::Triangle() : Object{ } {
	m_tag = "Triangle";
	m_drawMode = GL_TRIANGLES;
}

Triangle::Triangle(float x, float y, float size) : Object{ x, y, 0.f, size, 0.f, 0.f } {
	m_originPoints[0] = { 0.f, m_size.x * 2.f / 3.f, 0.f };
	m_originPoints[1] = { -m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	m_originPoints[2] = { m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	m_tag = "Triangle";
	m_drawMode = GL_TRIANGLES;
}

Triangle::Triangle(const Vec3F& position, const Size3F& size) : Object{ position, size } {
	m_originPoints[0] = { 0.f, m_size.x * 2.f / 3.f, 0.f };
	m_originPoints[1] = { -m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	m_originPoints[2] = { m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	m_tag = "Triangle";
	m_drawMode = GL_TRIANGLES;
}

Triangle::Triangle(const Vec3F& position, const Size3F& size, const Color3F& color) : Object{ position, size } {
	m_originPoints[0] = { 0.f, m_size.x * 2.f / 3.f, 0.f };
	m_originPoints[1] = { -m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	m_originPoints[2] = { m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	for (int i = 0; i < 3; ++i) {
		m_vertexColor[i] = color;
	}
	m_tag = "Triangle";
	m_drawMode = GL_TRIANGLES;
}

Triangle::Triangle(const Vec3F& position, const Size3F& size, const Color3F* colors) : Object{ position, size } {
	m_originPoints[0] = { 0.f, m_size.x * 2.f / 3.f, 0.f };
	m_originPoints[1] = { -m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	m_originPoints[2] = { m_size.x / 2.f, -m_size.x / 3.f, 0.f };
	for (int i = 0; i < 3; ++i) {
		m_vertexColor[i] = colors[i];
	}
	m_tag = "Triangle";
	m_drawMode = GL_TRIANGLES;
}

Triangle::Triangle(const Vec3F* positions, const Color3F* colors) {
	m_origin = GetGravityPoint(positions);
	for (int i = 0; i < 3; ++i) {
		m_originPoints[i] = positions[i] - m_origin;
		m_vertexColor[i] = colors[i];
	}
	m_tag = "Triangle";
	m_drawMode = GL_TRIANGLES;
}

Vec3F Triangle::GetGravityPoint(const Vec3F* vectors) {
	Vec3F rtVec{ };
	for (int i = 0; i < 3; ++i) {
		rtVec.x += vectors[i].x;
		rtVec.y += vectors[i].y;
	}
	rtVec.x /= 3.f;
	rtVec.y /= 3.f;
	return rtVec;
}

void Triangle::SetRotateAngle(float rotateAngle) {
	m_rotateAngle = rotateAngle;
}

void Triangle::AddRotateAngle(float addAngle) {
	m_rotateAngle += addAngle;
}

void Triangle::SetDrawMode(int drawMode) {
	m_drawMode = drawMode;
}

void Triangle::SetColor(const Color3F& color) {
	for (int i = 0; i < 3; ++i) {
		m_vertexColor[i] = color;
	}
}

void Triangle::SetColor(const Color3F& color1, const Color3F& color2, const Color3F& color3) {
	m_vertexColor[0] = color1;
	m_vertexColor[1] = color2;
	m_vertexColor[2] = color3;
}

void Triangle::SetColor(const Color3F* color) {
	for (int i = 0; i < 3; ++i) {
		m_vertexColor[i] = color[i];
	}
}

void Triangle::SetColorRandom() {
	Color3F randColor = GetRandomColor3F(0.f, 1.f);
	for (int i = 0; i < 3; ++i) {
		m_vertexColor[i] = randColor;
	}
}

void Triangle::SetColorRandomVertex() {
	for (int i = 0; i < 3; ++i) {
		m_vertexColor[i] = GetRandomColor3F(0.f, 1.f);
	}
}

bool Triangle::IsInBox(const Vec3F& lt, const Vec3F& rb) {
	Vec3F drawVec[3]{ };
	for (int i = 0; i < 3; ++i) {
		drawVec[i] = m_originPoints[i].Rotate(m_rotateAngle);
		drawVec[i] = drawVec[i] + m_origin;
		if (isInBox(drawVec[i], lt, rb)) {
			return true;
		}
	}
	return false;
}

bool Triangle::CheckOut(const Vec3F& minWindow, const Vec3F& maxWindow) {
	Vec3F drawVec[3]{ };
	for (int i = 0; i < 3; ++i) {
		drawVec[i] = m_originPoints[i].Rotate(m_rotateAngle);
		drawVec[i] = drawVec[i] + m_origin;
		if (drawVec[i].x < minWindow.x or drawVec[i].y < minWindow.y or drawVec[i].x > maxWindow.x or drawVec[i].y > maxWindow.y) {
			return true;
		}
	}
	return false;
}

bool Triangle::OutX(const Vec3F& minWindow, const Vec3F& maxWindow) {
	Vec3F drawVec[3]{ };
	for (int i = 0; i < 3; ++i) {
		drawVec[i] = m_originPoints[i].Rotate(m_rotateAngle);
		drawVec[i] = drawVec[i] + m_origin;
		if (drawVec[i].x < minWindow.x) {
			m_origin.x += 1.f;
			return true;
		}
		else if (drawVec[i].x > maxWindow.x) {
			m_origin.x -= 1.f;
			return true;
		}
	}
	return false;
}

bool Triangle::OutY(const Vec3F& minWindow, const Vec3F& maxWindow) {
	Vec3F drawVec[3]{ };
	for (int i = 0; i < 3; ++i) {
		drawVec[i] = m_originPoints[i].Rotate(m_rotateAngle);
		drawVec[i] = drawVec[i] + m_origin;
		if (drawVec[i].y < minWindow.y) {
			m_origin.y += 1.f;
			return true;
		}
		else if (drawVec[i].y > maxWindow.y) {
			m_origin.y -= 1.f;
			return true;
		}
	}
	return false;
}

void Triangle::Move(float deltaTime) {
	m_origin.x += m_moveVec.x * deltaTime * m_moveSpeed;
	m_origin.y += m_moveVec.y * deltaTime * m_moveSpeed;
}

void Triangle::MoveToState(int moveState, float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow) {
	if (m_moveState != moveState) {
		prevMoveDir = MoveDir::null;
		prevMoveX = MoveDir::null;
		prevMoveY = MoveDir::null;
		rateMoveVec = MoveDir::down;
		rateMove = false;
	}
	m_moveState = moveState;

	switch (m_moveState) {
	case 1:
		MovePingPong(deltaTime, minWindow, maxWindow);
		break;

	case 2:
		MoveZig(deltaTime, minWindow, maxWindow);
		break;

	case 3:
	case 4:
	default:
		break;
	}
}

void Triangle::MoveZig(float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow) {	
	if (OutY(minWindow, maxWindow)) {
		if (prevMoveX == MoveDir::left or prevMoveX == MoveDir::null) {
			m_moveVec = MoveDir::right;
			prevMoveX = MoveDir::right;
			AddRotateAngle(90);
		}
		else {
			m_moveVec = MoveDir::left;
			prevMoveX = MoveDir::left;
			AddRotateAngle(-90);
		}

		if (prevMoveY == MoveDir::up or prevMoveY == MoveDir::null) {
			rateMoveVec = MoveDir::down;
			prevMoveY = MoveDir::down;
		}
		else {
			rateMoveVec = MoveDir::up;
			prevMoveY = MoveDir::up;
		}
		rateMove = false;
	}

	if (OutX(minWindow, maxWindow)) {
		if (prevMoveX == MoveDir::left or prevMoveX == MoveDir::null) {
			m_moveVec = MoveDir::right;
			prevMoveX = MoveDir::right;
			AddRotateAngle(-90);
		}
		else {
			m_moveVec = MoveDir::left;
			prevMoveX = MoveDir::left;
			AddRotateAngle(90);
		}
		rateMove = true;
	}

	if (!rateMove) {
		if (m_moveVec == MoveDir::null) {
			prevMoveX = MoveDir::right;
			m_moveVec = MoveDir::right;
		}
		Object::Move(m_moveVec, deltaTime, m_moveSpeed);
	}
	else {
		moveTime += deltaTime;
		if (moveTime > timeRate) {
			moveTime = 0.f;
			rateMove = false;
		}
		Object::Move(rateMoveVec, deltaTime, m_moveSpeed);
	}
}

void Triangle::MovePingPong(float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow) {
	if (m_moveVec == MoveDir::null) {
		m_moveVec = MoveDir::rightDown;
		prevMoveDir = MoveDir::rightDown;
	}

	if (OutX(minWindow, maxWindow)) {
		m_moveVec = MoveDir::null;
		if (prevMoveDir == MoveDir::rightUp) {
			m_moveVec = MoveDir::leftUp;
			prevMoveDir = MoveDir::leftUp;
		}
		else if (prevMoveDir == MoveDir::rightDown) {
			m_moveVec = MoveDir::leftDown;
			prevMoveDir = MoveDir::leftDown;
		}
		else if (prevMoveDir == MoveDir::leftUp) {
			m_moveVec = MoveDir::rightUp;
			prevMoveDir = MoveDir::rightUp;
		}
		else {
			m_moveVec = MoveDir::rightDown;
			prevMoveDir = MoveDir::rightDown;
		}
		AddRotateAngle(90);
	}
	else if (OutY(minWindow, maxWindow)) {
		if (prevMoveDir == MoveDir::rightUp) {
			m_moveVec = MoveDir::rightDown;
			prevMoveDir = MoveDir::rightDown;
		}
		else if (prevMoveDir == MoveDir::rightDown) {
			m_moveVec = MoveDir::rightUp;
			prevMoveDir = MoveDir::rightUp;
		}
		else if (prevMoveDir == MoveDir::leftUp) {
			m_moveVec = MoveDir::leftDown;
			prevMoveDir = MoveDir::leftDown;
		}
		else {
			m_moveVec = MoveDir::leftUp;
			prevMoveDir = MoveDir::leftUp;
		}
		AddRotateAngle(90);
	}

	Object::Move(m_moveVec, deltaTime, m_moveSpeed);
}

void Triangle::Update(float deltaTime) {
	
}

void Triangle::Render(Mesh* mesh) {
	mesh->SetDrawMode(m_drawMode); 

	Vec3F drawVec[3]{ };
	for (int i = 0; i < 3; ++i) {
		drawVec[i] = m_originPoints[i].Rotate(m_rotateAngle);
		drawVec[i] = drawVec[i] + m_origin;
		drawVec[i] = drawVec[i].ToGLCoordinate();
	}

	float vertBuf[]{
		drawVec[0].x, drawVec[0].y, drawVec[0].z, m_vertexColor[0].r, m_vertexColor[0].g, m_vertexColor[0].b,
		drawVec[1].x, drawVec[1].y, drawVec[1].z, m_vertexColor[1].r, m_vertexColor[1].g, m_vertexColor[1].b,
		drawVec[2].x, drawVec[2].y, drawVec[2].z, m_vertexColor[2].r, m_vertexColor[2].g, m_vertexColor[2].b,
	};
	unsigned int indexBuf[]{ 0, 1, 2 };

	mesh->SetVertexs(vertBuf, sizeof(vertBuf) / sizeof(float), 3);
	mesh->SetIndexBuffer(indexBuf, sizeof(indexBuf) / sizeof(unsigned int));
	mesh->Render();
}
