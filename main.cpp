#include "Engine.h"

Engine e{ };

int main(int argc, char* argv[])
{
	e.Init(&argc, argv);

	e.Loop();

	return 0;
}