#pragma once


#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>

namespace Long 
{
	class LONG_API Log
	{
	public:
		static void Init(); 

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private: 
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define LONG_CORE_ERROR(...)	::Long::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LONG_CORE_WARN(...)		::Long::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LONG_CORE_INFO(...)		::Long::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LONG_CORE_TRACE(...)	::Long::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LONG_CORE_FATAL(...)	::Long::Log::GetCoreLogger()->fatal(__VA_ARGS__)
//Core Client macros
#define LONG_ERROR(...)			::Long::Log::GetClientLogger->error(__VA_ARGS__)
#define LONG_WARN(...)			::Long::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LONG_INFO(...)			::Long::Log::GetClientLogger()->info(__VA_ARGS__)
#define LONG_TRACE(...)			::Long::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LONG_FATAL(...)			::Long::Log::GetClientLogger()->fatal(__VA_ARGS__)