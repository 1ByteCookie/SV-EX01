#include <Windows.h>
#include "MainWindow.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow Window(1280, 720);
	ShowWindow(Window.GetHandle(), nCmdShow);

	std::vector<Vertex> Vertices =
	{
		Vertex{ DirectX::XMFLOAT2(-0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		Vertex{ DirectX::XMFLOAT2( 0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		Vertex{ DirectX::XMFLOAT2( 0.5f, -0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		Vertex{ DirectX::XMFLOAT2(-0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) }
	};

	std::vector<unsigned int> Indices =
	{
		0, 1, 2,
		3, 0, 1
	};

	cBuffer Constants{};
	Constants.Model = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixTranslation(1.0f, 0.0f, 5.0f) *
		DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(30.0f)) *
		DirectX::XMMatrixPerspectiveLH(1.0f, 720.0f/1280.0f, 1.0f, 100.0f)
	);

	Mesh Triangle = Window.Resource()->CreateMesh(	Vertices,
													Indices,
													Constants,
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