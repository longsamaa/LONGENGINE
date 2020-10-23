#pragma once

#include "Long/Layer.h"
#include "Long/Events/MouseEvent.h"
#include "Long/Events/KeyEvent.h"
#include "Long/Application.h"

namespace Long
{
	class LONG_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(); 
		~ImGuiLayer(); 

		void OnUpdate(); 
		void OnEvent(Long::Event& event); 
		void OnDetach(); 
		void OnAttach();
	private: 
		bool OnMouseButtonPressEvent(MouseButtonPressedEvent &e); 
		bool OnMouseButtonReleaseEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e); 
		bool OnMouseScrolledEvent(MouseScrolledEvent& e); 
		bool OnKeyPressedEvent(KeyPressedEvent& e); 
		bool OnKeyReleasedEvent(KeyReleasedEvent& e); 
		bool OnKeyTypedEvent(KeyTypedEvent& e); 
		bool OnWindowResizeEvent(WindowResizeEvent& e); 
	private:
		float m_Time = 0.0f; 
	};
}