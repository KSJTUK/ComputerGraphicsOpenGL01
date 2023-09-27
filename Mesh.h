#pragma once

// VAO, VBO, EBO를 바인딩해서 삼각형을 그려줄 클래스
class Mesh {
public:
	Mesh();
	~Mesh();

	// 복사 연산 허용
	Mesh(const Mesh& ohter);
	Mesh& operator=(const Mesh& other);

private:
	// Vertex Buffer Object ID
	unsigned int m_vertexBufferObject{ };
	// Vertex Array Object ID
	unsigned int m_vertexArrayObject{ };
	// Element Buffer OBject ID
	unsigned int m_elemetBufferObject{ };

	// 그리기 모드 점, 선, 삼각형 등
	// default값은 삼각형(생성자에서 설정)
	unsigned int m_drawMode{ };

public:
	void Init();
	void SetVertexs(float* vertexBuffer, size_t bufferSize);
	void SetIndexBuffer(unsigned int* indexBuffer, size_t bufferSize);
	void SetDrawMode(unsigned int mode);
	void Render();
};