#include "mxpch.h"
#include <glad/glad.h>

#include "Bootstrapper.h"

#include <imgui.h>
#include "Renderer/Events/WindowEvent.h"
#include "Renderer/Core.h"
#include "Renderer/Core/Layer/ImGui/GuiLayer.h"
#include "Renderer/Components/Renderer.h"

namespace RenderingEngine
{
	Bootstrapper* Bootstrapper::s_Instance = nullptr;

	Bootstrapper::Bootstrapper()
	{
		s_Instance = this;

		m_LayerStack = LayerStack();

		m_Window = std::make_unique<Window>();
		m_Window->SetEventCallback(BIND_FUN(OnEvent));

		AddLayer(new GuiLayer());
	}

	void Bootstrapper::Run()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		while (m_Running)
		{
			m_Window->EveryUpdate();

			GuiLayer::Begin();

			for (const auto layer : m_LayerStack)
				layer->EveryUpdate();

			GuiLayer::End();
		}
	}

	void Bootstrapper::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FUN(OnWindowCloseEvent));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_FUN(OnKeyPressedEvent));

		for (const auto layer : m_LayerStack)
		{
			if (e.Active == false)
				return;

			layer->OnEvent(e);
		}
	}

	void Bootstrapper::AddLayer(Layer* layer)
	{
		m_LayerStack.Push(layer);
		layer->Attach();
	}

	bool Bootstrapper::OnWindowCloseEvent(const WindowCloseEvent& e)
	{
		LOG_CORE_INFO("Shutdown");
		LOG_CORE_INFO("{0}", e.ToString());

		m_Running = false;
		return false;
	}

	bool Bootstrapper::OnKeyPressedEvent(const KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == GLFW_KEY_ESCAPE)
		{
			LOG_CORE_INFO("Shutdown");

			m_Running = false;
			return true;
		}

		return false;
	}
}