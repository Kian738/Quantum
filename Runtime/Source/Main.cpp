#include "Core/Launch.h"

#ifndef PROJECT_NAME
	#error "PROJECT_NAME must be defined"
#endif

const char* GetProjectPath()
{
	return PROJECT_NAME;
}
