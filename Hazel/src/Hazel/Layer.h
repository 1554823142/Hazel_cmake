#pragma once

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();


        // 如果被禁用的layer就不会被渲染更新, 也不用接受事件, 即将此layer从stack中隐藏起来
		
		// 初始化
		virtual void OnAttach() {}

		// 释放资源
		virtual void OnDetach() {}

		// 每帧更新与渲染
		virtual void OnUpdate() {}      // 图层更新时调用(每一帧更新)

		// 事件处理
		virtual void OnEvent(Event& event) {}


		
		virtual void OnImGuiRender() {} // ImGui渲染时调用

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}