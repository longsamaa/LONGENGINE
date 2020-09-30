#include "Long.h"
class Sandbox : public Long::Application
{
public:
	Sandbox()
	{
	
	}
	~Sandbox()
	{
	
	}
};

Long::Application* Long::CreateApplication() 
{
	return new Sandbox(); 
}