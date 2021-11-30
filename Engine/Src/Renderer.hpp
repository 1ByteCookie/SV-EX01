#pragma once

#include <Windows.h>
#include <d3d11.h>
#include "Mesh.hpp"

class Renderer
{
public:
	void Clear(float R, float G, float B, float A);
	void Present();
	void InitViewPort();
	void Draw(Mesh& mesh);

	Renderer(HWND Handle);
	~Renderer();
	Renderer(const Renderer& Object) = delete;

	inline auto& GetDevice() { return m_Device; }

private:

	HWND						m_Handle;

	IDXGISwapChain*				m_SwapChain;
	ID3D11Device*				m_Device;
	ID3D11DeviceContext*		m_ImmediateContext;

	ID3D11RenderTargetView*		m_RenderTarget;
};