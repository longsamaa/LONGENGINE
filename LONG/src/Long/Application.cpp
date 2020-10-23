#include "Longpch.h"
#include "Application.h"
#include "Log.h"
#include <glad/glad.h>

namespace Long {
	Application* Application::s_Instance = nullptr; 
	Application::Application() 
	{
		s_Instance = this; 
		LONG_CORE_ASSERT(!s_Instance, "Application already exists!"); 
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent)); 
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e) 
	{
		//Window event
		Long::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Long::WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosedEvent)); 

		//Layer Onevent
		for (auto it = Application::m_LayerStack.end(); it != Application::m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break; 
		}

		LONG_CORE_INFO("{0}",e); 
	}

	void Application::Run()
	{
		while (Application::m_running)
		{
			glClearColor(1, 0, 1, 1); 
			glClear(GL_COLOR_BUFFER_BIT); 

			for (Layer* layer : Application::m_LayerStack)
			{
				layer->OnUpdate(); 
			}

			Application::m_Window->OnUpdate(); 
		}
	}

	bool Application::OnWindowClosedEvent(Long::WindowCloseEvent& event)
	{
		Application::m_running = false; 
		return true; 
	}

	//Layer

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer); 
		layer->OnAttach(); 
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay); 
		overlay->OnAttach();
	}
}
