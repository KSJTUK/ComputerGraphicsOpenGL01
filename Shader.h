#pragma once

#include "pch.h"

class Shader {
public:
	Shader();
	~Shader();

private:
	unsigned int m_shaderProgram{ };
	unsigned int m_VBO{ };
	unsigned int m_VAO{ };
	
	// 쉐이더 파일의 내용을 저장할 함수
	std::string m_vsFileContents{ };
	std::string m_fragFileContents{ };

public:
	// 쉐이더 파일 내용을 불러오는 함수
	void RoadVertexShaderFile(const char* filePath);
	void RoadFragmentShaderFIle(const char* filePaht);

	// 쉐이더 작성 함수들
	void AddShader(GLenum shaderType);
	void AttachShader();
	void CompileShader();
	void CreateShaderProgram();
};

