#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

// ���� ���̴� Ŭ����, ���� �Լ����� ����, ������ ����
#include <iostream>
#include <string>
#include <vector>

// ������ �������� �������� ������ ����ü ����
typedef struct WindowInfo {
	int x;
	int y;
	size_t width;
	size_t height;
	float fWidth;
	float fHeight;
} WIN_INFO;