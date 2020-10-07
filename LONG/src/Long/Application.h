#pragma once
#include "Longpch.h"
#include "Core.h"
#include "Window.h"
#include "Long/Events/ApplicationEvent.h"
#include "../LayerStack.h"

namespace Long {
	class LONG_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e); 
		bool OnWindowClosedEvent(Long::WindowCloseEvent& event); 

		//Layer

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer); 
		//To be define Client;
	private: 
		std::unique_ptr<Window> m_Window; 
		bool m_running = true;
		LayerStack m_LayerStack; 
	};
	Application* CreateApplication(); 
}

