#include "Core/Launch.h"

// TODO: Rewrite
#ifndef PROJECT_NAME
	#error "PROJECT_NAME must be defined"
#endif

const char* GetProjectPath()
{
	return PROJECT_NAME;
}
