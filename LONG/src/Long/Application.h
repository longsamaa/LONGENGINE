#pragma once
#include "Core.h"

namespace Long {
	class LONG_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		//To be define Client; 
	};
	Application* CreateApplication(); 
}

