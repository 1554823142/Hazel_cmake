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


	// ���������������赥��������
	extern HAZEL_API Application* CreateApplication();
}