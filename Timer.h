#pragma once

// 타이머 기능을 할 클래스
class Timer{ 
public:
	Timer();
	~Timer();

private:
	// 쿼리를 이용하여 시간을 잰다
	union _LARGE_INTEGER* m_tick{ nullptr };
	union _LARGE_INTEGER* m_prev{ nullptr };

	// 시간 배속 설정 변수
	float m_timeScale{ 1.f };
	// 델타 타임
	float m_deltaTime{ };
	// 시작부터 흐른 시간을 저장할 변수
	float m_timeElapsed{ 0.0f };
	// 프레임 관련 변수
	int m_frameCount{ };
	float m_fps{ };

public:
	//Setter and Getter
	void SetTimeScale(float timeScale);
	float GetDeltaTime() const;
	float GetTimeScale() const;
	double GetFrame() const;

public:
	void Init();
	void Update();
};

