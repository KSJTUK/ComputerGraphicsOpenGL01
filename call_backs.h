#pragma once

// 그리기 함수 GLvoid(*drawFunc)(GLvoid)
void renderFunc();

// 사이즈 변화 대응 함수 GLvoid(*reshapeFunc)(int, int)
void reshapeFunc(int, int);

// idle time 함수 GLvoid(*idleFunc)(GLvoid)
void idleFunc();

// 키보드 입력 처리 함수 GLvoid(*keyboardFunc)(unsigned char, int, int, int)
void keyboardFunc(unsigned char, int, int, int);

// 키보드 특수 키 처리 함수
void specialkeyFunc(int, int, int);

// 마우스 입력 처리함수
void mouseFunc(int, int, int, int);
void mouseLeftDown(int, int, int);
void mouseRightDown(int, int, int);

// 마우스 모션 함수 (클릭: motion, 기본 passiveMotion)
void mouseMotion(int, int);
void mousePassiveMotion(int, int);

// 마우스 휠 입력 처리함수
void mouseWheel(int, int, int);

// 타이머 함수
// deltaTime 사용예정