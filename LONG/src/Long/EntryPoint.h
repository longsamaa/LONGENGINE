#pragma once

#ifdef LONG_PLATFORM_WINDOWS
extern Long::Application* Long::CreateApplication(); 

int main(int argc, char** argv)
{
	Long::Log::Init(); 
	LONG_CORE_WARN("Initialized Log!"); 
	int a = 5; 
	LONG_INFO("Hello! Var = {0}", a); 
	auto app = Long::CreateApplication(); 
	app->Run();
	delete app;
}

#endif

