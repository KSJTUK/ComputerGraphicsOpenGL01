#include "solution6.h"
#include "solution8.h"
#include "solution9.h"

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
	SDF;

	solution9::solution(&argc, argv);

	return 0;
}