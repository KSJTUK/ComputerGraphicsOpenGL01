#include "pch.h"
#include "Engine.h"
#include "call_backs.h"
#include "Shader.h"
#include "Mesh.h"
#include "Timer.h"
#include "ShapeManager.h"

Engine::Engine() {
	m_windowInfo.x = 100;
	m_windowInfo.y = 100;
	m_windowInfo.width = 800;
	m_windowInfo.height = 600;
	m_windowInfo.fWidth = static_cast<float>(m_windowInfo.width);
	m_windowInfo.fHeight = static_cast<float>(m_windowInfo.height);

	std::string title{ "OpenGL Project 01" };
	std::string::size_type size = title.size();
	m_windowTitle = new char[size + 1] {};
	memcpy(m_windowTitle, title.c_str(), size + 1);
}

Engine::~Engine() {
	// �����Ҵ� ��ü�� �޸� �Ҵ� ����
	//if (m_timer) delete m_timer;
	//m_timer = nullptr;
	SafeDeletePointer(m_shader);
	SafeDeletePointer(m_shapeManager);
	SafeDeleteArrayPointer(m_windowTitle);
}

// �ݹ��Լ��� ���
void Engine::SubscribeCallbacks() {
	glutDisplayFunc(renderFunc);
	glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutIdleFunc(idleFunc);
	glutSpecialFunc(specialkeyFunc);
}

void Engine::SetWindowSize(int windowWidth, int windowHeight) {
	m_windowInfo.width = static_cast<size_t>(windowWidth);
	m_windowInfo.height = static_cast<size_t>(windowHeight);
	m_windowInfo.fWidth = static_cast<float>(windowWidth);
	m_windowInfo.fHeight = static_cast<float>(windowHeight);
}


void Engine::Init(int* argc, char** argv) {
	// glut���̺귯�� �ʱ�ȭ
	glutInit(argc, argv);

	// ������ ��¸�� ����(������۸�, RGBA)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	// ������ ũ��, ��ǥ ����
	glutInitWindowPosition(m_windowInfo.x, m_windowInfo.y);
	glutInitWindowSize(m_windowInfo.width, m_windowInfo.height);

	// ������ ����
	glutCreateWindow(m_windowTitle);

	// glew ���̺귯�� �ʱ�ȭ
	glewExperimental = GL_TRUE;
	try {
		if (glewInit() != GLEW_OK) {
			throw "GLEW ���̺귯�� �ʱ�ȭ ����";
		}
	}
	catch (std::string expn) {
		std::cerr << expn << std::endl;
		exit(EXIT_FAILURE);
	}

	SubscribeCallbacks();

	// Ÿ�̸� �ʱ�ȭ
	m_timer = new Timer{ };
	m_timer->Init();

	// ���̴� ���α׷� �ʱ�ȭ
	m_shader = new Shader{ };
	m_shader->CreateShaderProgram();
	
	// ������ �Ŵ��� �ʱ�ȭ
	m_shapeManager = new ShapeManager{ };

	glPointSize(3.f);
}

void Engine::ReSizeWindow(int w, int h) {
	m_windowInfo.width = w;
	m_windowInfo.height = h;
	m_windowInfo.fWidth = static_cast<float>(m_windowInfo.width);
	m_windowInfo.fHeight = static_cast<float>(m_windowInfo.height);
}

void Engine::Update() {
	m_timer->Update();
	m_deltaTime = m_timer->GetDeltaTime();
	std::cout << m_deltaTime << std::endl;
	std::cout << m_timer->GetFrame() << std::endl;
	m_shapeManager->Update(m_deltaTime);
}

void Engine::Render() {
	m_shader->UseProgram();
	m_shapeManager->Render();
}

ShapeManager* Engine::GetShapeManager() const {
	return m_shapeManager;
}

void Engine::SubscribeDrawFunc(void(*func)(void)) {
	glutDisplayFunc(func);
}

void Engine::SubscribeMouseFunc(void(*func)(int, int, int, int)) {
	glutMouseFunc(func);
}

void Engine::SubscribeKeyboardUpfunc(void(*func)(unsigned char, int, int)) {
	glutKeyboardUpFunc(func);
}

void Engine::SubscribeKeyboardFunc(void(*func)(unsigned char, int, int)) {
	glutKeyboardFunc(func);
}

void Engine::SubscribeReshapeFunc(void(*func)(int, int)) {
	glutReshapeFunc(func);
}

void Engine::SubscribeIdleFUnc(void(*func)(void)) {
	glutIdleFunc(func);
}

void Engine::Loop() {
	glutMainLoop();
}

void Engine::LoopEnd() {
	glutLeaveMainLoop();
}
