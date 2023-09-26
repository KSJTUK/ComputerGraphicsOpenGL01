#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

// 자주 쓰이는 클래스, 전역 함수들을 선언, 정의할 파일
#include <iostream>
#include <string>
#include <vector>

// 생성할 윈도우의 정보들을 저장할 구조체 정의
typedef struct WindowInfo {
	int x;
	int y;
	size_t width;
	size_t height;
	float fWidth;
	float fHeight;
} WIN_INFO;