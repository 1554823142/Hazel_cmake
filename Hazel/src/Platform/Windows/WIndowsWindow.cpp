#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

#include <Hazel/Log.h>
#include <GLAD/glad.h>
// #include <GLFW/glfw3.h>

namespace Hazel {
	
	static bool s_GLFWInitialized = false;		// 静态变量, 用于记录GLFW是否初始化,防止重复初始化

	static void GLFWErrorCallback(int error, const char* description)
	{
		HZ_CORE_ERROR("GLFW ERROR ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);		// 实现Window抽象类的静态工厂方法, 返回WIndows平台下的窗口实例
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();			// GLFW库函数
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);		// 将刚刚创建的窗口的OpenGL上下文设置为当前线程的上下文。
		
		// 增加glad loader(glad的核心功能)
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize GLAD");
		
		glfwSetWindowUserPointer(m_Window, &m_Data);		// m_Data为数据指针, 可以存储任意的数据, GLFW的回调函数可以通过这个指针获取到与窗口有关的数据
		SetVSync(true);			// 设置窗口的垂直同步（VSync）为开启状态


		// set GLFW callbacks

		// 设置glfw窗口大小的回调函数
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window ,int height, int width){
			WindowData& w_data = *(WindowData*)(glfwGetWindowUserPointer(window));		// 返回用户定义windows指针所指向的值
			w_data.Height = height;
			w_data.Width = width;
			WindowResizeEvent event(height, width);		// 创建一个设置窗口大小的Event
			w_data.EventCallback(event);
		});

		// 设置glfw窗口关闭回调事件
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
			WindowData& w_data = *(WindowData*)(glfwGetWindowUserPointer(window));		// 返回用户定义windows指针所指向的值
			WindowCloseEvent event;
			w_data.EventCallback(event);
		});


		// 鼠标回调
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});


		// 键盘回调
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
			WindowData& w_data = *(WindowData*)(glfwGetWindowUserPointer(window));		// 返回用户定义windows指针所指向的值

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					w_data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					w_data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, true);
					w_data.EventCallback(event);
					break;
				}
			}
		});

		// 滚轮回调
		// a mouse wheel or scrolling area of a touchpad.
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});


		
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();		// 处理所有待处理的窗口事件
		glfwSwapBuffers(m_Window);		// 交换前后缓冲区，显示渲染结果
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}