#pragma once

#include <Windows.h>
#include <d3d11.h>

class Renderer
{
public:
	void Clear(float R, float G, float B, float A);
	void Present();

	Renderer(HWND Handle);
	~Renderer();
	Renderer(const Renderer& Object) = delete;

	void DrawInit();
	void Draw();

private:

	HWND						m_Handle;

	IDXGISwapChain*				m_SwapChain;
	ID3D11Device*				m_Device;
	ID3D11DeviceContext*		m_ImmediateContext;

	ID3D11RenderTargetView*		m_RenderTarget;

	//===================
	ID3D11Buffer*			m_VertexBuffer;
	ID3D11Buffer*			m_IndexBuffer;
	ID3D11VertexShader*		m_VS;
	ID3D11PixelShader*		m_PS;
};