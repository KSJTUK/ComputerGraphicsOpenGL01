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
