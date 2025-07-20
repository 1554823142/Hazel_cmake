#include "hzpch.h"
#include "Application.h"

#include "Input.h"
#include <glad/glad.h>
// #include <GLFW/glfw3.h>
namespace Hazel {

    Application* Application::s_Instance = nullptr;
// std::bind:
// p1: 类成员函数指针
// p2: 类对象地址
// p3: 占位符参数位置
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application() {

        HZ_ASSERT(!s_Instance, "Application already exists!");

        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());   // 单例模式
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));     // 回调Application的OnEvent函数

        // unsigned int id;
        // glGenVertexArrays(1, &id);
    }

    Application::~Application() {
        // 可以留空
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverLayer(Layer* layer)
    {   
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }


    void Application::Run()
    {     
        while(m_Running){
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            for(Layer* layer : m_LayerStack){
                layer->OnUpdate();
            }

            // ImGui渲染
            for(Layer* layer : m_LayerStack){
                layer->OnImGuiRender();
            }
            
            auto [x, y] = Input::GetMousePosition();
            HZ_CORE_TRACE("{0}, {1}", x, y);
            m_Window->OnUpdate();           // 这是可以处理窗口事件输入的OnUpdate
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ){
            (*--it)->OnEvent(e);        // Application的OnEvent将事件传递给Application所有的Layer层的OnEvent
            if(e.Handled)       // 如果OverLayer处理了此事件, 就不再继续, 即**拦截**
                break;
        }
    }


    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;
        return true;
    }


    
}
