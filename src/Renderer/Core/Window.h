#pragma once

#include <string>
#include <GLFW/glfw3.h>

#include "Renderer/Events/Event.h"

namespace RenderingEngine
{
	struct WindowProperties
	{
		std::string Name;
		uint16_t Width, Height;
		bool VSync;

		explicit WindowProperties(const std::string& name = "Rendering Engine",
		                          uint16_t width = 800,
		                          uint16_t height = 600)
		{
			Name = name;
			Width = width;
			Height = height;
			VSync = true;
		}
	};

	class Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		explicit Window(const WindowProperties& properties = WindowProperties());
		~Window();

		[[nodiscard]] uint16_t GetWidth() const { return m_Data.Properties.Width; }
		[[nodiscard]] uint16_t GetHeight() const { return m_Data.Properties.Height; }
		[[nodiscard]] bool VSyncEnabled() const { return m_Data.Properties.VSync; }
		[[nodiscard]] GLFWwindow* const& GetNativeWindow() const { return m_Window; }

		void EveryUpdate() const;
		void SetEventCallback(const EventCallbackFunc& callback) { m_Data.Callback = callback; }
		void SetVSync(bool isEnabled);

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			WindowProperties Properties;

			EventCallbackFunc Callback;
		};

		WindowData m_Data;
	};
}