#include "Object.h"
#include "Mesh.h"

Object::Object() {
}

Object::~Object() {
}

Object::Object(float x, float y, float z, float sizeX, float sizeY, float sizeZ) {
	m_origin = { x, y, z };
	m_size.x = sizeX;
	m_size.y = sizeY;
	m_size.z = sizeZ;
}

Object::Object(const Vec3F& position, const Size3F& size) {
	m_origin = position;
	m_size.x = size.x;
	m_size.y = size.y;
	m_size.z = size.z;
}

void Object::SetMoveSpeed(float speed) {
	m_moveSpeed = speed;
}

void Object::SetOriginPoint(const Vec3F& setPt) {
	m_origin = setPt;
}

void Object::Move(const Vec3F& moveDir) {
	Vec3F moveVec = { moveDir.x * m_moveSpeed, moveDir.y * m_moveSpeed, 0.f };
	m_origin = m_origin + moveDir;
}

void Object::Move(const Vec3F& moveDir, float deltaTime, float speed) {
	m_origin.x += moveDir.x * deltaTime * speed;
	m_origin.y += moveDir.y * deltaTime * speed;
}
