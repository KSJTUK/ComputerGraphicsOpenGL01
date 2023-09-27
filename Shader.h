#pragma once

class Shader {
public:
	Shader();
	~Shader();

private:
	unsigned int m_shaderProgram{ };
	unsigned int m_fragmentShader{ };
	unsigned int m_vertexShader{ };
	
	// 쉐이더 파일의 내용을 저장할 변수
	char* m_vertexShaderFileContents{ };
	char* m_fragmentShaderFileContents{ };

	// 버퍼, 배열 오브젝트들
	unsigned int m_VBO{ };
	unsigned int m_VAO{ };
	unsigned int m_EBO{ };

public:
	// 쉐이더 파일 내용을 불러오는 함수
	void RoadVertexShaderFile(const char* filePath);
	void RoadFragmentShaderFile(const char* filePaht);

	// 쉐이더 작성 함수들
	void CompileShaders();
	void AttachAndLinkShaders();
	void CreateShaderProgram();
	void UseProgram();

	// 버퍼, 배열 오브젝트들 생성 함수
	void CreateBuffers();

public:
	// Getter 함수들
	unsigned int GetShaderProgramID() const { return m_shaderProgram; }
	unsigned int GetVAO() const { return m_VAO; }
	unsigned int GetVBO() const { return m_VBO; }
	unsigned int GetEBO() const { return m_EBO; }
};

