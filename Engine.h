#pragma once

// 생성할 윈도우의ㅡ 정보를 담을 구조체 정의
typedef struct WindowInfo {
	int x;
	int y;
	int width;
	int height;
	float fWidth;
	float fHeight;
	char* windowTitle;
} WIN_INFO;

class Engine{
public:
	// 기본 생성, 소멸자
	Engine();
	~Engine();

	// 객체의 복사를 금지
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

private:
	WIN_INFO m_windowInfo;
	char* m_windowTitle{ };
	class Mesh* m_mesh{ nullptr };
	class Shader* m_shader{ nullptr };
	class Timer* m_timer{ nullptr };
	class ShapeManager* m_shapeManager{ nullptr };

	float m_deltaTime{ };

private:
	// 멤버함수 내에서만 쓰일 함수들 정의
	void SubscribeCallbacks();

public:
	void SubscribeDrawFunc(void(*func)(void));
	void SubscribeIdleFUnc(void(*func)(void));
	void SubscribeReshapeFunc(void(*func)(int, int));
	void SubscribeMouseFunc(void(*func)(int, int, int, int));
	void SubscribeMouseMotionFunc(void(*func)(int, int));
	void SubscribePassiveMotionFunc(void(*func)(int, int));
	void SubscribeKeyboardFunc(void(*func)(unsigned char, int, int));
	void SubscribeKeyboardUpfunc(void(*func)(unsigned char, int, int));

public:
	size_t GetWindowWidth() const { return m_windowInfo.width; }
	size_t GetWindowHeight() const { return m_windowInfo.height; }
	float GetWindowWidthF() const { return m_windowInfo.fWidth; }
	float GetWindowHeightF() const { return m_windowInfo.fHeight; }

	float GetDeltaTime() const { return m_deltaTime; };

	class ShapeManager* GetShapeManager() const;

	void SetWindowSize(int windowWidth, int windowHeight);
	
public:
	// 기본 멤버 객체들 생성, 윈도우 생성, 콜백함수 설정등을 하는 함수
	void Init(int*, char**);
	// reshape콜백 함수가 불려올때 윈도우 크기를 변경할 함수
	void ReSizeWindow(int, int);
	// 게임 로직 업데이트 함수
	void Update();
	// 렌더링 명령 함수
	void Render();
	// 게임 루프함수
	void Loop();
	// 게임 종료함수
	void LoopEnd();
};