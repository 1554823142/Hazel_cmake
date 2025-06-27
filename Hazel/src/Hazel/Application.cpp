#include "hzpch.h"
#include "Application.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"
namespace Hazel {

    Application::Application() {
        // 可以留空
    }

    Application::~Application() {
        // 可以留空
    }
    void Application::Run()
    {     
        std::cout << "hello\n";
        WindowResizeEvent e(1200, 700);  
        HZ_CORE_TRACE(e.ToString());
        while (true);
    }
}


