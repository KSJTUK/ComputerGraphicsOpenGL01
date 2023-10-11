#include "Polygon.h"
#include "Mesh.h"
#include "constants.h"
#include "pch.h"

PolygonF::PolygonF(const Vec3F& origin, float size, int vertexSize) : Object{  } {
	m_origin = origin;
	m_prevOrigin = m_origin;
	m_vertexSize = vertexSize % m_vertexLimit;
	if (m_vertexSize == 0) {
		m_vertexSize = 1;
	}

	m_polygonSize = size;

	if (m_vertexSize == 1) {
		m_state = POINT;
	}
	else if (m_vertexSize == 2) {
		m_state = LINE;
	}
	else {
		m_state = POLYGON;
	}

	CreatePolygonState(m_state);
	CreateIndexBuffer(m_state);
}

PolygonF::~PolygonF() {
	SafeDeleteArrayPointer(m_indexBuffer);
}

bool PolygonF::IsPointInPolygon(const Vec3F& point) {
	int crossCount{ };
	Vec3F* polygonPt = new Vec3F[m_vertexSize];
	auto iter = m_pointList.begin();
	++iter;
	for (int i = 0; i < m_vertexSize; ++i, ++iter) {
		polygonPt[i] = (*iter);
	}

	for (int i = 0; i < m_vertexSize; ++i) {
		int j = (i + 1) % m_vertexSize;
		if ((polygonPt[i].y >= point.y) != (polygonPt[j].y >= point.y)) {
			double revSlope = ((polygonPt[j].x - polygonPt[i].x) / (polygonPt[j].y - polygonPt[i].y));
			double actX = revSlope * (point.y - polygonPt[i].y) + polygonPt[i].x;
			if (point.x < actX) {
				++crossCount;
			}
		}
	}
	delete[] polygonPt;
	return (crossCount & 1); //  홀수 일경우 true리턴
}

void PolygonF::DeleteOrigin() {
	m_pointList.pop_front();
	m_vertexSize -= 1;
}

bool PolygonF::IsPointIn(const Vec3F& point) {
	bool rtVal{ false };
	switch (m_state) {
	case POINT:
		rtVal = IsPointInPoint(point);
		break;

	case LINE:
		rtVal = IsPointInPoint(point);
		break;

	case POLYGON:
		rtVal = IsPointInPolygon(point);
		break;
	}
	return rtVal;
}

void PolygonF::SetOriginPoint(const Vec3F& point) {
	Object::SetOriginPoint(point);
	OriginMove();
}

bool PolygonF::Collision(const PolygonF& other) {
	float originLength{ m_polygonSize * m_polygonSize };
	float otherLength{ (other.m_polygonSize * other.m_polygonSize) };
	float diffX{ m_origin.x - other.m_origin.x }, diffY{ m_origin.y - other.m_origin.y };
	float diffLength{ diffX * diffX + diffY * diffY };
	if (originLength + otherLength > diffLength) {
		return true;
	}
	return false;
}

bool PolygonF::OutX(const Vec3F& minWindow, const Vec3F& maxWindow) {
	for (auto& v : m_pointList) {
		if (v.x < minWindow.x) {
			for (auto& a : m_pointList) {
				a.x += 10.f;
			}
			return true;
		}
		
		if (v.x > maxWindow.x) {
			for (auto& a : m_pointList) {
				a.x -= 10.f;
			}
			return true;
		}
	}
	return false;
}

bool PolygonF::OutY(const Vec3F& minWindow, const Vec3F& maxWindow) {
	for (auto& v : m_pointList) {
		if (v.y < minWindow.y) {
			for (auto& a : m_pointList) {
				a.y += 10.f;
			}
			return true;
		}

		if (v.y > maxWindow.y) {
			for (auto& a : m_pointList) {
				a.y -= 10.f;
			}
			return true;
		}
	}
	return false;
}

void PolygonF::ResetSpecialMoveVariables(int moveState, const Vec3F& minWindow, const Vec3F& maxWindow) {
	prevMoveDir = MoveDir::null;
	prevMoveX = MoveDir::null;
	prevMoveY = MoveDir::null;
	rateMoveVec = MoveDir::down;
	rateMove = false;
	moveTime = 0.f;
	m_spiralMoveAngle = 0.f;
	m_spiralMoveRadius = 0.f;
	m_spiralRadiusDir = 1.f;
	m_rotateAngle = 0.f;
	m_moveSpeed = GetRandomF(100.f, 300.f);
	if (moveState == 3) {
		m_outCountX = 1;
		m_outCountY = 1;
		m_origin = { GetRandomF(-200.f, 200.f), maxWindow.y - ((m_size.x / 2.f)) * m_outCountY, 0.f };
		m_moveVec = MoveDir::left;
		prevMoveX = MoveDir::left;
		rateMove = false;
		rateMoveVec = MoveDir::null;
		m_moveWhileSt = m_origin;
	}
	else if (moveState == 2) {
		m_origin = { GetRandomF(-200.f, 200.f), GetRandomF(-200.f, 200.f), 0.f };
		float r = GetRandomF(0.f, 2.f);
		m_moveVec = r <= 1.f ? MoveDir::left : MoveDir::right;
		rateMoveVec = MoveDir::down;
	}
	else if (moveState == 1) {
		float r = GetRandomF(0.f, 2.f);
		m_moveVec = r <= 1.f ? MoveDir::rightDown : MoveDir::leftDown;
	}
}

void PolygonF::Move(float deltaTime){
	for (auto& v : m_pointList) {
		v.x += m_moveSpeed * m_moveVec.x * deltaTime;
		v.y += m_moveSpeed * m_moveVec.y * deltaTime;
	}
	m_origin = m_pointList.front();
	m_prevOrigin = m_pointList.front();
}

void PolygonF::MoveToState(int moveState, float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow) {
	if (m_moveState != moveState) {
		ResetSpecialMoveVariables(moveState, minWindow, maxWindow);
	}
	m_moveState = moveState;

	switch (m_moveState) {
	case 1:
		MovePingPong(deltaTime, minWindow, maxWindow);
		break;

	case 2:
		MoveZig(deltaTime, minWindow, maxWindow);
		break;

	default:
		break;
	}
}

void PolygonF::MoveToState(float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow) {
	switch (m_moveState) {
	case 1:
		MovePingPong(deltaTime, minWindow, maxWindow);
		break;

	case 2:
		MoveZig(deltaTime, minWindow, maxWindow);
		break;

	default:
		break;
	}
}

void PolygonF::MoveZig(float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow) {
	if (OutY(minWindow, maxWindow)) {
		if (prevMoveX == MoveDir::left or prevMoveX == MoveDir::null) {
			m_moveVec = MoveDir::right;
			prevMoveX = MoveDir::right;
		}
		else {
			m_moveVec = MoveDir::left;
			prevMoveX = MoveDir::left;
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
		}
		else {
			m_moveVec = MoveDir::left;
			prevMoveX = MoveDir::left;
		}
		rateMove = true;
	}

	if (!rateMove) {
		if (m_moveVec == MoveDir::null) {
			prevMoveX = MoveDir::right;
			m_moveVec = MoveDir::right;
		}
		Move(deltaTime);
	}
	else {
		moveTime += deltaTime;
		if (moveTime > timeRate) {
			moveTime = 0.f;
			rateMove = false;
		}
		Move(deltaTime);
	}
}

void PolygonF::MovePingPong(float deltaTime, const Vec3F& minWindow, const Vec3F& maxWindow) {
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
	}

	Move(deltaTime);
}

void PolygonF::OriginMove() {
	Vec3F moveVec = m_origin - m_prevOrigin;
	for (auto& e : m_pointList) {
		e += moveVec;
	}
	m_prevOrigin = m_origin;
}

bool PolygonF::IsPointInPoint(const Vec3F& point) {
	Vec3F pointBox[2]{
		{ m_origin.x - 10.f, m_origin.y + 10.f, 0.f },
		{ m_origin.x + 10.f, m_origin.y - 10.f, 0.f }
	};
	return isInBox(point, pointBox[0], pointBox[1]);
}

bool PolygonF::IsPointInLine(const Vec3F& point) {
	Vec3F lineBox[2]{ };
	std::list<Vec3F>::const_iterator iter = m_pointList.begin();
	for (int i = 0; i < 2; ++i, ++iter) {
		lineBox[i] = (*iter);
	}

	lineBox[0].x -= 10.f;
	lineBox[1].y -= 10.f;
	lineBox[1].x += 10.f;
	lineBox[0].y += 10.f;

	return isInBox(point, lineBox[0], lineBox[1]);
}

void PolygonF::CreatePoint() {
	m_indexBufferSize = POINT;
	m_vertexBufferSize = POINT * 6;
	m_drawVertexSize = POINT;
	m_drawMode = GL_POINTS;

	m_pointList.push_back(m_origin);
	m_colorList.push_back(GetRandomColor3F(0.f, 1.f));
}

void PolygonF::CreateLine() {
	m_indexBufferSize = LINE;
	m_vertexBufferSize = LINE * 6;
	m_drawVertexSize = LINE;
	m_drawMode = GL_LINES;

	Vec3F line[2]{
		{ m_origin.x - m_polygonSize / 2.f, m_origin.y, 0.f },
		{ m_origin.x + m_polygonSize / 2.f, m_origin.y, 0.f }
	};
	m_pointList.push_back(line[0]);
	m_pointList.push_back(line[1]);
	m_colorList.push_back(GetRandomColor3F(0.f, 1.f));
	m_colorList.push_back(GetRandomColor3F(0.f, 1.f));
}

void PolygonF::CreatePolygon() {
	m_indexBufferSize = m_vertexSize * 3;
	m_vertexBufferSize = (m_vertexSize + 1) * 6;
	m_drawVertexSize = m_vertexSize * 3;

	m_drawMode = GL_TRIANGLES;

	m_pointList.push_back(m_origin);

	Vec3F setPoint{ m_polygonSize, 0.f, 0.f };
	if (m_vertexSize == 4) {
		setPoint = setPoint.Rotate(45);
	}
	else {
		setPoint = setPoint.Rotate(90);
	}

	float rotateAngle = 360.f / m_vertexSize;
	for (int i = 0; i < m_vertexSize; ++i) {
		Vec3F pushPoint = setPoint;
		float angle = rotateAngle * i;
		pushPoint = pushPoint.Rotate(angle);
		pushPoint += m_origin;
		m_pointList.push_back(pushPoint);
	}

	for (int i = 0; i < m_vertexSize + 1; ++i) {
		m_colorList.push_back(GetRandomColor3F(0.f, 1.f));
	}
}

void PolygonF::CreateIndexBuffer(state st) {
	m_indexBuffer = new unsigned int[m_indexBufferSize];
	switch (st) {
	case POINT:
		m_indexBuffer[0] = 0;
		break;

	case LINE:
		for (int i = 0; i < LINE; ++i) {
			m_indexBuffer[i] = i;
		}
		break;

	case POLYGON:
		for (int i = 0; i < m_vertexSize; ++i) {
			int curIdxStart{ i * 3 };
			m_indexBuffer[curIdxStart] = 0;
			m_indexBuffer[curIdxStart + 1] = i + 1;
			m_indexBuffer[curIdxStart + 2] = i + 2;
		}
		m_indexBuffer[m_indexBufferSize - 1] = 1;
		break;
	}
	
}

float* PolygonF::PointAndLineToVBuffer() {
	float* vertexBuffer{ new float[m_vertexBufferSize] };
	auto pListIter = m_pointList.begin();
	auto cListIter = m_colorList.begin();
	for (int i = 0; i < m_vertexSize; ++i, ++pListIter, ++cListIter) {
		Vec3F vec = (*pListIter);
		Color3F color = (*cListIter);
		vec = vec.ToGLCoordinate();
		for (int v = 0; v < 3; ++v) {
			vertexBuffer[i * 6 + v] = vec[v];
		}

		for (int c = 3; c < 6; ++c) {
			vertexBuffer[i * 6 + c] = color[c % 3];
		}
	}
	return vertexBuffer;
}

float* PolygonF::PolygonToVBuffer() {
	float* vertexBuffer{ new float[(m_vertexSize + 1) * 6] };
	auto pListIter = m_pointList.begin();
	auto cListIter = m_colorList.begin();
	for (int i = 0; i < m_vertexSize + 1; ++i, ++pListIter, ++cListIter) {
		Vec3F vec = (*pListIter);
		Color3F color = (*cListIter);
		vec = vec.ToGLCoordinate();
		for (int v = 0; v < 3; ++v) {
			vertexBuffer[i * 6 + v] = vec[v];
		}

		for (int c = 3; c < 6; ++c) {
			vertexBuffer[i * 6 + c] = color[c % 3];
		}
	}
	return vertexBuffer;
}

void PolygonF::SetDrawMode(int drawMode) {
	if (m_state == POLYGON) {
		m_drawMode = drawMode;
	}
}

void PolygonF::CreatePolygonState(state st) {
	switch (st) {
	case POINT:
		CreatePoint();
		break;

	case LINE:
		CreateLine();
		break;

	case POLYGON:
		CreatePolygon();
		break;
	}
}

float* PolygonF::VectorListToVBuffer(state st) {
	float* vertexBuffer{ nullptr };
	switch (st) {
	case POLYGON:
		vertexBuffer = PolygonToVBuffer();
		break;

	default:
		vertexBuffer = PointAndLineToVBuffer();
		break;
	}
	return vertexBuffer;
}

void PolygonF::Update(float deltaTime) {
}

void PolygonF::Render(Mesh* renderer) {
	float* vertexBuffer = VectorListToVBuffer(m_state);
	renderer->SetDrawMode(m_drawMode);
	renderer->SetVertexs(vertexBuffer, m_vertexBufferSize, m_drawVertexSize);
	renderer->SetIndexBuffer(m_indexBuffer, m_indexBufferSize);
	renderer->Render();
	delete[] vertexBuffer;
}
