#pragma once

#include "pch.h"

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
	std::string m_windowTitle{ };
	class Shader* m_shader{ nullptr };
	class Timer* m_timer{ nullptr };

private:
	// 멤버함수 내에서만 쓰일 함수들 정의
	void SubscribeCallbacks();
	
public:
	// 기본 멤버 객체들 생성, 윈도우 생성, 콜백함수 설정등을 하는 함수
	void Init(int*, char**);
	// reshape콜백 함수가 불려올때 윈도우 크기를 변경할 함수
	void ReSizeWindow(int, int);
	// 게임 로직 업데이트 함수
	void Update();
	// 게임 루프함수
	void Loop();
};