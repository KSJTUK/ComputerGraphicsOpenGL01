#include "constants.h"

namespace Random {
	std::random_device rd;
	std::default_random_engine dre{ rd() };
}

namespace Colors {
	Color3F red{ 1.f, 0.f, 0.f };
	Color3F blue{ 0.f, 1.f, 0.f };
	Color3F green{ 0.f, 0.f, 1.f };
	Color3F white{ 1.f, 1.f, 1.f };
	Color3F black{ 0.f, 0.f, 0.f };
	Color3F gray{ 0.5f, 0.5f, 0.5f };
	Color3F magenta{ 1.f, 0.f, 1.f };
	Color3F yellow{ 1.f, 1.f, 0.f };
	Color3F cyan{ 0.f, 1.f, 1.f };
}

namespace MoveDir {
	Vec3F up{ 0.f, 1.f, 0.f };
	Vec3F down{ 0.f, -1.f, 0.f };
	Vec3F left{ -1.f, 0.f, 0.f };
	Vec3F right{ 1.f, 0.f, 0.f };
	Vec3F leftUp{ -1.f, 1.f, 0.f };
	Vec3F leftDown{ -1.f, -1.f, 0.f };
	Vec3F rightUp{ 1.f, 1.f, 0.f };
	Vec3F rightDown{ 1.f, -1.f, 0.f };
	Vec3F null{ 0.f, 0.f, 0.f };
}

namespace Constant {
	float f_Pi{ 3.141592f };
	long double Pi{ 3.141592 };
	float gravity{ 9.8f };
}

float GetRandomF(float min, float max)
{
	std::uniform_real_distribution<float> urd{ min, max };
	return urd(Random::dre);
}
