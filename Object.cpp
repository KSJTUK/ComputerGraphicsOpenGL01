#include "Object.h"
#include "Mesh.h"

Object::Object() {
	m_mesh = new Mesh{ };
	m_mesh->Init();
}

Object::~Object() {
	if (m_mesh) delete m_mesh;
	m_mesh = nullptr;
}

void Object::Render() {
	m_mesh->Render();
}
