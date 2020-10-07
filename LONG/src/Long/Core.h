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

#ifdef LONG_ENABLE_ASSERT
	#define LONG_ASSERT(x,...) 
	{
		if (!(x))
		{
			LONG_ERROR("Assertion Failed: {0}", __VA_ARGS__); 
			__debugbreak; 
		}
	}
	#define LONG_ASSERT(x,...) 
	{
		if (!(x))
		{
			LONG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);
			__debugbreak;
		}
	}
#else
	#define LONG_ASSERT(x, ...)
	#define LONG_CORE_ASSERT(x, ...)
#endif // LONG_ENABLE_ASSERT



#define BIT(x) (1 << x)
