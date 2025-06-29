#pragma once

#include "Hazel/Core.h"
#include "Layer.h"

namespace Hazel {

	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;       // LayerStack本质就是维护一个Layer的vector
		std::vector<Layer*>::iterator m_LayerInsert;		// 这个作为普通Layer和OverLayer的分界线
	};

}