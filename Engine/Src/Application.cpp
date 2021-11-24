#include <Windows.h>
#include "MainWindow.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow Window(1280, 720);
	ShowWindow(Window.GetHandle(), nCmdShow);

	MSG Message{};
	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);

		Window.GFX()->Clear(0.1f, 0.0f, 0.3f, 1.0f);
		Window.GFX()->Present();
	}

	return 0;
}