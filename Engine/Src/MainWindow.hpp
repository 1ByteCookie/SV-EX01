#pragma once

#include <Windows.h>

class MainWindow
{
	class WC_MAIN_WINDOW
	{
	public:
		static WC_MAIN_WINDOW Instance;
		PCWSTR GetName() const { return L"Main Window"; }

	private:
		WC_MAIN_WINDOW();
		~WC_MAIN_WINDOW();
		WC_MAIN_WINDOW(const WC_MAIN_WINDOW& Object) = delete;
	};

public:
	MainWindow(int Width, int Height);
	~MainWindow();
	MainWindow(const MainWindow& Object) = delete;

	inline HWND GetHandle() const { return m_Handle; }

private:
	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND	m_Handle;
	int		m_Width;
	int		m_Height;
};