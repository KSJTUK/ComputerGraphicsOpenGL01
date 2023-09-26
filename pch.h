#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

// 자주쓰이는 클래스, 전역함수, 라이브러리등을 정의, 선언할 파일
// 표준 라이브러리
#include <iostream>
#include <string>
#include <vector>

// 사용자 정의 라이브러리
#include "call_backs.h"

// 클래스, 구조체
// 생성할 윈도우의ㅡ 정보를 담을 구조체 정의
typedef struct WindowInfo {
	int x;
	int y;
	size_t width;
	size_t height;
	float fWidth;
	float fHeight;
	char* windowTitle;
} WIN_INFO;