#pragma once

// 전역변수들 저장
// extern 키워드로 사용
#include <random>
#include "types.h"

namespace Random {
	extern std::random_device rd;
	extern std::default_random_engine dre;
}

namespace Colors {
	extern Color3F red;
	extern Color3F blue;
	extern Color3F green;
	extern Color3F white;
	extern Color3F black;
	extern Color3F gray;
	extern Color3F magenta;
	extern Color3F yellow;
	extern Color3F cyan;
}

namespace MoveDir {
	extern Vec3F up;
	extern Vec3F down;
	extern Vec3F left;
	extern Vec3F right;
	extern Vec3F leftUp;
	extern Vec3F leftDown;
	extern Vec3F rightUp;
	extern Vec3F rightDown;
	extern Vec3F null;
}

namespace Constant {
	extern float f_Pi;
	extern long double Pi;
	extern float gravity;
}

float GetRandomF(float min, float max);