#include <Windows.h>
#include "MainWindow.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow Window(1280, 720);
	ShowWindow(Window.GetHandle(), nCmdShow);

	std::vector<Vertex> Vertices =
	{
		Vertex{ DirectX::XMFLOAT2(-0.5f, -0.5f) },
		Vertex{ DirectX::XMFLOAT2( 0.0f,  0.5f) },
		Vertex{ DirectX::XMFLOAT2( 0.5f, -0.5f) }
	};

	std::vector<unsigned int> Indices =
	{
		0, 1, 2
	};

	Mesh Triangle = Window.Resource()->CreateMesh(	Vertices,
													Indices,
													L"Shaderbin/VertexShader.cso",
													L"ShaderBin/PixelShader.cso");

	MSG Message{};
	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);

		Window.GFX()->Clear(0.1f, 0.0f, 0.3f, 1.0f);

		Window.GFX()->Draw(Triangle);
		
		Window.GFX()->Present();
	}

	return 0;
}