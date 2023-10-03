#pragma once

#include "Engine.h"
#include "constants.h"
#include "ShapeManager.h"
#include "Point.h"
#include "Triangle.h"
#include "types.h"

namespace solution7 {
	Engine e7{ };

	void solution7(int* argc, char** argv) {
		e7.Init(argc, argv);

		e7.Loop();
	}
}