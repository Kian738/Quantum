#include "Core/Launch.h"

#ifndef PROJECT_NAME
	#error "PROJECT_NAME must be defined"
#endif

Quantum::String GetProjectName()
{
	return PROJECT_NAME;
}
