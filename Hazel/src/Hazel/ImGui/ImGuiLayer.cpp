#include "hzpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Hazel/Application.h"

namespace Hazel {

ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
{
}

ImGuiLayer::~ImGuiLayer()
{
}

void ImGuiLayer::OnAttach()
{
    // 1. 创建ImGui上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // 2. 设置ImGui样式
    ImGui::StyleColorsDark();

    // 3. 初始化平台/渲染后端
    Application& app = Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130"); // 你的GLSL版本
}


void ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::OnUpdate()
{
    // 1. 更新ImGui显示尺寸和时间
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

    float time = (float)glfwGetTime();
    io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;

    // 2. 新帧
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 3. 你的ImGui内容
    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    // 4. 渲染
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event& event)
{
    // 转发事件给ImGui
    // 由于新版本的imGUI开箱即用, 所以不必实现

    
    // EventDispatcher dispatcher(event);

    // dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    // dispatcher.Dispatch<MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    // dispatcher.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    // dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
    // dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    // // dispatcher.Dispatch<KeyTypedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
    // dispatcher.Dispatch<KeyReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    // dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));

}

// bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &e)
// {
//     ImGuiIO& io = ImGui::GetIO();
//     io.MouseDown[e.GetMouseButton()] = true;

//     return false;
// }
// bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e)
// {
//     ImGuiIO& io = ImGui::GetIO();
//     io.MouseDown[e.GetMouseButton()] = false;

//     return false;
// }
// bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &e)
// {
//     ImGuiIO& io = ImGui::GetIO();
// 	io.MousePos = ImVec2(e.GetX(), e.GetY());


//     return false;
// }
// bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &e)
// {
//     ImGuiIO& io = ImGui::GetIO();
//     io.MouseWheelH += e.GetXOffset();
//     io.MouseWheel += e.GetYOffset();
//     return false;
// }
// bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &e)
// {
//     ImGuiIO& io = ImGui::GetIO();
//     // io.KeysDown[e.GetKeyCode()] = true;

//     // io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
//     // io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
//     // io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
//     // io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
    
//     return false;
// }
// bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &e)
// {
//     ImGuiIO& io = ImGui::GetIO();
// 		// io.KeysDown[e.GetKeyCode()] = false;

// 		// return false;

//     return false;
// }

// bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
// {
//     ImGuiIO& io = ImGui::GetIO();
//     int keycode = e.GetKeyCode();
//     if (keycode > 0 && keycode < 0x10000)
//         io.AddInputCharacter((unsigned short)keycode);

//     return false;
// }

// bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent &e)
// {
//     ImGuiIO& io = ImGui::GetIO();
//     io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
//     io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
//     glViewport(0, 0, e.GetWidth(), e.GetHeight());
//     return false;
// }
}