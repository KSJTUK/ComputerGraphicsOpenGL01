#include "Engine.h"
#include "call_backs.h"

Engine::Engine() {
	m_windowInfo.x = 100;
	m_windowInfo.y = 100;
	m_windowInfo.width = 800;
	m_windowInfo.height = 600;
	m_windowInfo.fWidth = static_cast<float>(m_windowInfo.width);
	m_windowInfo.fHeight = static_cast<float>(m_windowInfo.height);

	m_windowTitle = "OpenGL_PG1";
}

Engine::~Engine() {
	// �����Ҵ� ��ü�� �޸� �Ҵ� ����
	//if (m_timer) delete m_timer;
	//m_timer = nullptr;
	//if (m_shader) delete m_shader;
	//m_shader = nullptr;
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


void Engine::Init(int* argc, char** argv) {
	// glut���̺귯�� �ʱ�ȭ
	glutInit(argc, argv);

	// ������ ��¸�� ����(������۸�, RGBA)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	// ������ ũ��, ��ǥ ����
	glutInitWindowPosition(m_windowInfo.x, m_windowInfo.y);
	glutInitWindowSize(m_windowInfo.width, m_windowInfo.height);

	// ������ ����
	glutCreateWindow(m_windowTitle.c_str());

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
}

void Engine::ReSizeWindow(int w, int h) {
	m_windowInfo.width = w;
	m_windowInfo.height = h;
	m_windowInfo.fWidth = static_cast<float>(m_windowInfo.width);
	m_windowInfo.fHeight = static_cast<float>(m_windowInfo.height);
}

void Engine::Update() {
}

void Engine::Loop() {
	glutMainLoop();
}