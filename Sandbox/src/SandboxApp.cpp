#include "Long.h"

class TestLayer : public Long::Layer
{
public:
	TestLayer() : Layer("Test") {}

	void OnUpdate() override
	{
		LONG_INFO("TestLayer::Update"); 
	}

	void OnEvent(Long::Event& event) override
	{
		LONG_TRACE("{0}", event);
	}
};




class Sandbox : public Long::Application
{
public:
	Sandbox()
	{
		Application::PushLayer(new TestLayer()); 
		Application::PushOverlay(new Long::ImGuiLayer()); 
	}
	~Sandbox()
	{
	
	}
};

Long::Application* Long::CreateApplication() 
{
	return new Sandbox(); 
}