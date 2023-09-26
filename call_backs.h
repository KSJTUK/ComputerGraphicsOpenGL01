#pragma once

// 그리기 콜백함수
void renderFunc();

// 윈도우 사이즈 변경 처리 함수
void reshapeFunc(int, int);

// idle time 함수
void idleFunc();

// 키보드 입력처리 함수
void keyboardFunc(unsigned char, int, int);
void keyboardUpFunc(unsigned char, int, int);

// 키보드 특수키 처리함수
void specialkeyFunc(int, int, int);

// 마우스 입력 처리함수
void mouseFunc(int, int, int, int);
void mouseLeftDown(int, int, int);
void mouseRightDown(int, int, int);

// 마우스 모션함수
void mouseMotion(int, int);
void mousePassiveMotion(int, int);

// 마우스 휠 입력함수
void mouseWheel(int, int, int);