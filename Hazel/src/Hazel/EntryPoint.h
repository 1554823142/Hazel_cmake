#pragma once

//#define HZ_PLATFORM_WINDOWS

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv) {

	Hazel::Log::Init();
	HZ_CORE_ERROR("something");
	HZ_CORE_INFO("dffdfff");
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif