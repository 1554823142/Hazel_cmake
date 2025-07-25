#include <Hazel.h>



#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer() : Layer("Example Layer")
	{
		auto cam = camera(7.5f, {0.5f, 0.5f});
		HZ_INFO("cam.length: {0}", cam.length());
	}

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