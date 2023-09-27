#include "Timer.h"
#include "pch.h"
#include <Windows.h>

Timer::Timer() { }
Timer::~Timer() {
	SafeDeletePointer(m_tick);
	SafeDeletePointer(m_prev);
}

void Timer::Init() {
	m_prev = new LARGE_INTEGER;
	m_tick = new LARGE_INTEGER;
}