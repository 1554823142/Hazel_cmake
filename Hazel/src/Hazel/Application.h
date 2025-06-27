#pragma once

#include "Core.h"


namespace Hazel {
	class HAZEL_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};


	// 声明工厂函数（需单独导出）
	Application* CreateApplication();
}