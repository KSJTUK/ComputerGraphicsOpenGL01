#include "Shader.h"
#include "pch.h"

Shader::Shader() { }
Shader::~Shader() { }

void Shader::RoadVertexShaderFile(const char* filePath) {
	std::fstream vertexFile{ filePath, std::ios::in };

	try {
		if (!vertexFile.is_open()) {
			throw "vertex shader file open error";
		}
	}
	catch (std::string expn) {
		std::cerr << expn << std::endl;
	}

	std::string contents{ };
	std::string line{ };
	while (!vertexFile.eof()) {
		std::getline(vertexFile, line);
		contents.append(line + "\n");
	}

	m_vsFileContents = contents.c_str();

	// 테스트용
	std::cout << "contents\n";
	std::cout << m_vsFileContents << "\n";

	vertexFile.close();
}

void Shader::RoadFragmentShaderFile(const char* filePath) {
	std::fstream fragmentFile{ filePath, std::ios::in };

	try {
		if (!fragmentFile.is_open()) {
			throw "fragment shader file open error";
		}
	}
	catch (std::string expn) {
		std::cerr << expn << std::endl;
	}

	std::string contents{ };
	std::string line{ };
	while (!fragmentFile.eof()) {
		std::getline(fragmentFile, line);
		contents.append(line + "\n");
	}

	m_fragFileContents = contents.c_str();

	// 테스트용
	std::cout << "contents\n";
	std::cout << m_fragFileContents << "\n";

	fragmentFile.close();
}