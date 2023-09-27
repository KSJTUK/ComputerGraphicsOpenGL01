#pragma once
#include "Object.h"

class Point : public Object {
public:
	Point() : Object{ } { }
	Point(float x, float y) : Object{ x, y } { }
	~Point() { }

private:
	void Move(int moveDir);
	void SetPt(float x, float y);
	void Update();
	void Render() override;
};

