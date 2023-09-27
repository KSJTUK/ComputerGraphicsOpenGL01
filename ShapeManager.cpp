#include "ShapeManager.h"
#include "Point.h"

void ShapeManager::CreatePoint(float x, float y) {
	m_shapeList.push_back(new Point{ x, y });
}

void ShapeManager::Update() {
	for (auto& e : m_shapeList) {
		e->Update();
	}
}

void ShapeManager::Render() {
	for (auto& e : m_shapeList) {
		e->Render();
	}
}

void ShapeManager::Clear() {
	m_shapeList.clear();
}
