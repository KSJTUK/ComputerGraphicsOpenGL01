#pragma once

// 전역변수들 저장
// extern 키워드로 사용
#include <random>
#include "types.h"

namespace Random {
	extern std::random_device rd;
	extern std::default_random_engine dre{ rd() };
}

namespace Colors {
	extern Color3F red{ 1.f, 0.f, 0.f };
	extern Color3F blue{ 0.f, 1.f, 0.f };
	extern Color3F green{ 0.f, 0.f, 1.f };
	extern Color3F white{ 1.f, 1.f, 1.f };
	extern Color3F black{ 0.f, 0.f, 0.f };
	extern Color3F gray{ 0.5f, 0.5f, 0.5f };
	extern Color3F magenta{ 1.f, 0.f, 1.f };
	extern Color3F yellow{ 1.f, 1.f, 0.f };
	extern Color3F cyan{ 0.f, 1.f, 1.f };
}

namespace MoveDir {
	extern Vec3F up{ 0.f, 1.f, 0.f };
	extern Vec3F down{ 0.f, -1.f, 0.f };
	extern Vec3F left{ -1.f, 0.f, 0.f };
	extern Vec3F right{ 1.f, 0.f, 0.f };
	extern Vec3F leftUp{ -1.f, 1.f, 0.f };
	extern Vec3F leftDown{ -1.f, -1.f, 0.f };
	extern Vec3F rightUp{ 1.f, 1.f, 0.f };
	extern Vec3F rightDown{ 1.f, -1.f, 0.f };
}

namespace Constant {
	extern float f_Pi{ 3.141592f };
	extern long double Pi{ 3.141592 };
	extern float gravity{ 9.8f };
}