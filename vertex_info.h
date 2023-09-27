#pragma once
float vPositionList[] = {
		0.5f, 0.5f, 0.0f, 1.f, 0.f, 0.f, // 우측 상단
		0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f,// 우측 하단
		-0.5f, -0.5f, 0.0f, 0.f, 0.f, 1.f,// 좌측 하단
		-0.5f, 0.5f, 0.0f, 1.f, 0.f, 1.f// 좌측 상단
};
unsigned int index[] = {
	0, 1, 3, // 첫 번째 삼각형
	1, 2, 3 // 두 번째 삼각형
};