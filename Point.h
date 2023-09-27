#pragma once
#include "Object.h"

class Point : public Object {
public:
	Point() : Object{ } { }
	~Point() { }

private:
	void Move(int moveDir);
	void SetPt(float x, float y);
	void Update();
};

