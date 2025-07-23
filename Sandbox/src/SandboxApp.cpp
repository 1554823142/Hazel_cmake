#include <Hazel.h>

class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer() : Layer("Example Layer"){	}

	void OnUpdate() override {
		// HZ_INFO("ExampleLayer::Update");

		if(Hazel::Input::IsKeyPressed(/*GLFW_KEY_TAB*/HZ_KEY_TAB)){		// 为了不使用GLFW的原生键码
			HZ_TRACE("Tab is pressed!");
		}
	}

	void OnEvent(Hazel::Event& event) override {
		// HZ_TRACE("{0}", event.ToString());

		if(event.GetEventType() == Hazel::EventType::KeyPressed){
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;

			HZ_TRACE("{0}" ,(char)e.GetKeyCode());
		}
	}
};
												

class Sandbox : public Hazel::Application {
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverLayer(new Hazel::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}