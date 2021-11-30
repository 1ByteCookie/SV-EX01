#include "MainWindow.hpp"

MainWindow::WC_MAIN_WINDOW MainWindow::WC_MAIN_WINDOW::Instance;

MainWindow::WC_MAIN_WINDOW::WC_MAIN_WINDOW()
{
	WNDCLASS wcMainWindow{};
	wcMainWindow.lpfnWndProc	= MainWindow::WindowProcedure;
	wcMainWindow.hInstance		= GetModuleHandle(NULL);
	wcMainWindow.lpszClassName	= Name();
	RegisterClass(&wcMainWindow);
}

MainWindow::WC_MAIN_WINDOW::~WC_MAIN_WINDOW()
{
	UnregisterClass(Name(), GetModuleHandle(NULL));
}

MainWindow::MainWindow(int Width, int Height)
	:m_Width(Width), m_Height(Height)
{
	m_Handle = CreateWindowEx(
		0,
		WC_MAIN_WINDOW::Get().Name(),
		L"Scene",
		WS_OVERLAPPEDWINDOW,
		
		CW_USEDEFAULT, CW_USEDEFAULT,
		m_Width, m_Height,

		NULL,
		NULL,
		GetModuleHandle(NULL),
		this
	);

	m_Renderer = std::make_unique<Renderer>(m_Handle);
	m_Manager = std::make_unique<ResourceManager>(m_Renderer->GetDevice());
}

MainWindow::~MainWindow()
{
	DestroyWindow(m_Handle);
}

LRESULT CALLBACK MainWindow::WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MainWindow* This;
	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* CreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		This = reinterpret_cast<MainWindow*>(CreateStruct->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)This);

		This->m_Handle = hwnd;
	}
	else
	{
		This = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (This)
	{
		return This->HandleMessage(uMsg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

LRESULT CALLBACK MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		case WM_LBUTTONUP:
		{
			OutputDebugString(L"Hello World!\n");
			return 0;
		}
	}

	return DefWindowProc(m_Handle, uMsg, wParam, lParam);
}