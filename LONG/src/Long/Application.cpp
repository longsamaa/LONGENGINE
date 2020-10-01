#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Long {
	Application::Application() 
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720); 
		//LONG_WARN(e);
		if (e.IsInCategory(EventCategoryInput)) 
		{
			LONG_WARN(e);
		}
		 
		while (true)
		{

		}
	}
}
