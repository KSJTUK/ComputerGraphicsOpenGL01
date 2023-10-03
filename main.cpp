#include "Engine.h"


#include <crtdbg.h>
#include <assert.h>

#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#define SDF _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF)
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else 
#define SDF NULL
#define new new
#endif

Engine e{ };

int main(int argc, char* argv[])
{
	e.Init(&argc, argv);
	SDF;

	e.Loop();

	return 0;
}