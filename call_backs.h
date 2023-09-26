#pragma once

// �׸��� �Լ� GLvoid(*drawFunc)(GLvoid)
void renderFunc();

// ������ ��ȭ ���� �Լ� GLvoid(*reshapeFunc)(int, int)
void reshapeFunc(int, int);

// idle time �Լ� GLvoid(*idleFunc)(GLvoid)
void idleFunc();

// Ű���� �Է� ó�� �Լ� GLvoid(*keyboardFunc)(unsigned char, int, int, int)
void keyboardFunc(unsigned char, int, int, int);

// Ű���� Ư�� Ű ó�� �Լ�
void specialkeyFunc(int, int, int);

// ���콺 �Է� ó���Լ�
void mouseFunc(int, int, int, int);
void mouseLeftDown(int, int, int);
void mouseRightDown(int, int, int);

// ���콺 ��� �Լ� (Ŭ��: motion, �⺻ passiveMotion)
void mouseMotion(int, int);
void mousePassiveMotion(int, int);

// ���콺 �� �Է� ó���Լ�
void mouseWheel(int, int, int);

// Ÿ�̸� �Լ�
// deltaTime ��뿹��