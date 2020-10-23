#pragma once
#include "Longpch.h"
#include "Core.h"
#include "Window.h"
#include "Long/Events/ApplicationEvent.h"
#include "Long/LayerStack.h"

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

		inline Window& GetWindow() { return *m_Window; };
		inline static Application& Get() { return *s_Instance;  }
		//To be define Client;
	private: 
		std::unique_ptr<Window> m_Window; 
		bool m_running = true;
		LayerStack m_LayerStack;  
	private:
		static Application* s_Instance;
	};
	Application* CreateApplication(); 
}

