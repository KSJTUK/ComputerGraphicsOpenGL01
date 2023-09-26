#pragma once

class Shader {
public:
	Shader();
	~Shader();

private:
	unsigned int m_shaderProgram{ };
	unsigned int m_VBO{ };
	unsigned int m_VAO{ };
	
	// 쉐이더 파일의 내용을 저장할 함수
	const char* m_vsFileContents{ };
	const char* m_fragFileContents{ };

public:
	// 쉐이더 파일 내용을 불러오는 함수
	void RoadVertexShaderFile(const char* filePath);
	void RoadFragmentShaderFile(const char* filePaht);

	// 쉐이더 작성 함수들
	void AddShaders();
	void AttachShader();
	void CompileShader();
	void CreateShaderProgram();
};

