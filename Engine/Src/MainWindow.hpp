#pragma once

#include <Windows.h>
#include <memory>
#include "Renderer.hpp"

class MainWindow
{
	class WC_MAIN_WINDOW
	{
	public:
		static const WC_MAIN_WINDOW& Get() { return Instance; }
		PCWSTR Name() const { return L"Main Window"; }

	private:
		WC_MAIN_WINDOW();
		~WC_MAIN_WINDOW();
		WC_MAIN_WINDOW(const WC_MAIN_WINDOW& Object) = delete;
		
		static WC_MAIN_WINDOW Instance;
	};

public:
	MainWindow(int Width, int Height);
	~MainWindow();
	MainWindow(const MainWindow& Object) = delete;

	inline HWND GetHandle() const { return m_Handle; }
	inline const auto& GFX() { return m_Renderer.get(); }

private:
	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND	m_Handle;
	int		m_Width;
	int		m_Height;

	std::unique_ptr<Renderer> m_Renderer;
};