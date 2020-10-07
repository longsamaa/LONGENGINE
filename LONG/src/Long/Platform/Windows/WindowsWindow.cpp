#include "Longpch.h"
#include "WindowsWindow.h"
#include "Long/Log.h"
#include "Long/Events/KeyEvent.h"
#include "Long/Events/MouseEvent.h"
#include "Long/Events/ApplicationEvent.h"

namespace Long
{
	static bool s_GLFWInitialized = false; 
	
	static void GLFWErrorCallback(int error, const char* description)
	{
		LONG_CORE_ERROR("GLFW Error {0} : {1}", error, description); 
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props); 
	}
	
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		WindowsWindow::Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		WindowsWindow::Shutdown(); 
	}


	//Private function
	void WindowsWindow::Init(const WindowProps& props)
	{
		WindowsWindow::m_Data.Title = props.Title; 
		WindowsWindow::m_Data.Width = props.Width; 
		WindowsWindow::m_Data.Height = props.Height; 

		LONG_CORE_INFO("Creating Window {0} ({1},{2})", WindowsWindow::m_Data.Title, WindowsWindow::m_Data.Width, WindowsWindow::m_Data.Height); 
		
		if (!s_GLFWInitialized)
		{
			int success = glfwInit(); 
			LONG_CORE_ASSERT("Could not intialize GLFW {0}", success); 
			glfwSetErrorCallback(GLFWErrorCallback); 
			s_GLFWInitialized = true; 
		}

		WindowsWindow::m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr); 
		glfwMakeContextCurrent(WindowsWindow::m_Window); 
		glfwSetWindowUserPointer(WindowsWindow::m_Window, &(WindowsWindow::m_Data)); 
		WindowsWindow::SetVSync(true); 
		

		//SET GLFW CALLBACKS
		glfwSetWindowSizeCallback(WindowsWindow::m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window); 
			data.Width = width;
			data.Height = height;

			Long::WindowResizeEvent event(width, height);
			data.EventCallback(event); 
		}); 

		glfwSetWindowCloseCallback(WindowsWindow::m_Window, [](GLFWwindow* window)
		{
			WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
			Long::WindowCloseEvent event; 
			data.EventCallback(event); 
		});
		//Set key callback
		glfwSetKeyCallback(WindowsWindow::m_Window, [](GLFWwindow* window, int key, int scancode, int action,int mods)
		{
			WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					Long::KeyPressedEvent event(key, 0);
					data.EventCallback(event); 
					break;
				}
				case GLFW_RELEASE:
				{
					Long::KeyReleasedEvent event(key); 
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					Long::KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});
		//set mouse button callback
		glfwSetMouseButtonCallback(WindowsWindow::m_Window, [](GLFWwindow* window,int button, int action, int modes)
		{
			WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					Long::MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					Long::MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});
		//set scroll callback
		glfwSetScrollCallback(WindowsWindow::m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
			Long::MouseScrolledEvent event((float)xOffset,(float)yOffset);
			data.EventCallback(event); 
		});
		//set mouse move callback
		glfwSetCursorPosCallback(WindowsWindow::m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
			Long::MouseMovedEvent event((float)x, (float)y); 
			data.EventCallback(event); 
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(WindowsWindow::m_Window); 
	}

	//Public function

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(WindowsWindow::m_Window); 
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1); 
		}
		else
		{
			glfwSwapInterval(0); 
		}

		WindowsWindow::m_Data.VSync = enabled; 
	}

	bool WindowsWindow::IsVSync() const
	{
		return WindowsWindow::m_Data.VSync; 
	}


}