#include "ShapeManager.h"
#include "Point.h"
#include "Triangle.h"
#include "pch.h"
#include "Mesh.h"

ShapeManager::ShapeManager() {
	m_mesh = new Mesh{ };

	m_mesh->Init();
}

ShapeManager::~ShapeManager() {
	for (auto& e : m_shapeList) {
		SafeDeletePointer(e);
	}
	m_shapeList.clear();
	for (auto& e : m_pointList) {
		SafeDeletePointer(e);
	}
	m_pointList.clear();
	SafeDeletePointer(m_mesh);
}

void ShapeManager::CreateTriangle(float x, float y, float size) {
	m_shapeList.push_back(new Triangle{ x, y, size });
}

void ShapeManager::CreatePoint(float x, float y) {
	m_pointList.push_back(new Point{ x, y, 0.f });
}

void ShapeManager::Update(float deltaTime) {
	for (auto& e : m_shapeList) {
		e->Update(deltaTime);
	}
	for (auto& e : m_pointList) {
		e->Update(deltaTime);
	}
}

void ShapeManager::Render() {
	for (auto& e : m_shapeList) {
		e->Render(m_mesh);
	}
	for (auto& e : m_pointList) {
		e->Render(m_mesh);
	}
}
