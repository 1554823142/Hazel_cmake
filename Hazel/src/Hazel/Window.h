#pragma once

#include "hzpch.h"

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hazel Engine",
			        unsigned int width = 1280,
			        unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};


    // 跨平台的window接口
	// Interface representing a desktop system based Window
	class HAZEL_API Window
	{
	public:

    // call back function, 用于事件处理
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		// 获取原生窗口句柄(GLFWWindow)
		virtual void* GetNativeWindow() const = 0;


        // 在各个平台上需要实现的函数, 静态方法用于创建窗口. 会根据平台不同返回不同的窗口实现
		static Window* Create(const WindowProps& props = WindowProps());
	};

}