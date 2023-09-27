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
	std::string line{ " " };
	while (!vertexFile.eof()) {
		std::getline(vertexFile, line);
		contents.append(line + "\n");
	}

	std::string::size_type size = contents.size();
	m_vertexShaderFileContents = new char[size + 1]{ };
	memcpy(m_vertexShaderFileContents, contents.c_str(), size + 1);

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
	std::string line{ " " };
	while (!fragmentFile.eof()) {
		std::getline(fragmentFile, line);
		contents.append(line + "\n");
	}

	std::string::size_type size = contents.size();
	m_fragmentShaderFileContents = new char[size + 1] {};
	memcpy(m_fragmentShaderFileContents, contents.c_str(), size + 1);

	fragmentFile.close();
}

void Shader::CompileShaders() {
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	// 쉐이더 소스코드 불러오기
	glShaderSource(m_vertexShader, 1, &m_vertexShaderFileContents, NULL);
	glShaderSource(m_fragmentShader, 1, &m_fragmentShaderFileContents, NULL);

	// 쉐이더 컴파일
	glCompileShader(m_vertexShader);
	glCompileShader(m_fragmentShader);
	
	// 쉐이더 컴파일 여부 확인
	int result{ };
	char errLog[BUFSIZ]{ };

	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(m_vertexShader, sizeof(errLog), NULL, errLog);
		std::cout << "vertex shader 컴파일 에러: " << errLog << std::endl;
	} 

	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(m_fragmentShader, sizeof(errLog), NULL, errLog);
		std::cout << "fragment shader 컴파일 에러: " << errLog << std::endl;
	}
}

void Shader::AttachAndLinkShaders() {
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	// 쉐이더 링크
	glLinkProgram(m_shaderProgram);

	// 쉐이더들이 제대로 링크 되었는지 확인
	int result{ };
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &result);
	if (!result) {
		std::cerr << "Shaders are not Linked" << std::endl;
	}
}

void Shader::CreateShaderProgram() {
	m_shaderProgram = glCreateProgram();
	RoadVertexShaderFile("vertex.glsl");
	RoadFragmentShaderFile("fragment.glsl");
	CompileShaders();
	AttachAndLinkShaders();
}

void Shader::UseProgram() {
	glUseProgram(m_shaderProgram);
}

void Shader::CreateBuffers() {
	float vPositionList[] = {
		0.5f, 0.5f, 0.0f, // 우측 상단
		0.5f, -0.5f, 0.0f, // 우측 하단
		-0.5f, -0.5f, 0.0f, // 좌측 하단
		-0.5f, 0.5f, 0.0f // 좌측 상단
	};
	unsigned int index[] = {
		0, 1, 3, // 첫 번째 삼각형
		1, 2, 3 // 두 번째 삼각형
	};

	// VAO 객체 생성 및 바인드
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// VBO 객체 생성 및 바인드
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// VAO에 데이터 저장
	glBufferData(GL_ARRAY_BUFFER, sizeof(vPositionList), vPositionList, GL_STATIC_DRAW);

	// EBO 객체 생성 및 바인드
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩

	// 인덱스 버퍼 내용 저장
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
