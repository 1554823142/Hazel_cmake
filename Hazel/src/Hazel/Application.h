#pragma once

#include "Core.h"
#include <iostream>

namespace Hazel {
	class HAZEL_API Application {
	public:
		Application();
		virtual ~Application();

		void Run()
		{
			std::cout << "Hello Hazel!\n";
			while(1);
		}
	};


	// 声明工厂函数（需单独导出）
	Application* CreateApplication();
}