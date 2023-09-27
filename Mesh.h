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

	float* m_vertexBuffer{ nullptr };
	float* m_indexBuffer{ nullptr };
	int m_vertexLocation{ };
	int m_colorLocation{ };

public:
	bool Init(const unsigned int* const shaderProgramID);
	void SetVertexs(int location, float* vertexBuffer, size_t bufferSize, size_t stride);
	void Update();
	void Render();
};