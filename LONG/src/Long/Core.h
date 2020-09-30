#pragma once

#ifdef LONG_PLATFORM_WINDOWS
	#ifdef LONG_BUILD_DLL
		#define LONG_API __declspec(dllexport)
	#else
		#define LONG_API __declspec(dllimport)
	#endif // LONG_BUILD_DLL
#else 
#error Long only supports Windows!
#endif // LONG_PLATFORM_WINDOWS

