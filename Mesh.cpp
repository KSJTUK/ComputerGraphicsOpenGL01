#include "Mesh.h"
#include "pch.h"

Mesh::Mesh() { }

Mesh::~Mesh() { }

void Mesh::Init() {
	// VAO 객체 생성 및 바인드
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	// VBO 객체 생성 및 바인드
	glGenBuffers(1, &m_vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);

	// EBO 객체 생성 및 바인드
	glGenBuffers(1, &m_elemetBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elemetBufferObject); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
}

void Mesh::SetVertexs(float* vertexBuffer, size_t bufferSize, size_t vertexSize, size_t stride) {
	// VAO에 데이터 저장
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Mesh::SetIndexBuffer(float* indexBuffer, size_t bufferSize) {
	// 인덱스 버퍼 내용 저장
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize * sizeof(float), indexBuffer, GL_STATIC_DRAW);
}

void Mesh::Render() {
	// shaderProgram 에서 UseProgram을 활성화 했다는 가정하에 수행
	glBindVertexArray(m_vertexArrayObject);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
