#include "Renderer.hpp"

void Renderer::Clear(float R, float G, float B, float A)
{
	float RGBA[] = { R, G, B, A };
	m_ImmediateContext->ClearRenderTargetView(m_RenderTarget, RGBA);
}

void Renderer::Present()
{
	m_SwapChain->Present(0, 0);
}

Renderer::Renderer(HWND Handle)
	:m_Handle(Handle), m_SwapChain(NULL), m_Device(NULL), m_ImmediateContext(NULL)
{
	DXGI_SWAP_CHAIN_DESC scDescriptor{};
	scDescriptor.BufferDesc.Width						= 0;
	scDescriptor.BufferDesc.Height						= 0;
	scDescriptor.BufferDesc.RefreshRate.Denominator		= 1;
	scDescriptor.BufferDesc.RefreshRate.Numerator		= 60;
	scDescriptor.BufferDesc.Format						= DXGI_FORMAT_R16G16B16A16_FLOAT;
	scDescriptor.SampleDesc.Count						= 1;
	scDescriptor.SampleDesc.Quality						= 0;
	scDescriptor.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDescriptor.BufferCount							= 1;
	scDescriptor.OutputWindow							= Handle;
	scDescriptor.Windowed								= TRUE;
	scDescriptor.SwapEffect								= DXGI_SWAP_EFFECT_DISCARD;
	scDescriptor.Flags									= 0;

	HRESULT HR = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scDescriptor,
		&m_SwapChain,
		&m_Device,
		NULL,
		&m_ImmediateContext
	);

	ID3D11Resource* BackBuffer;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&BackBuffer));
	m_Device->CreateRenderTargetView(BackBuffer, NULL, &m_RenderTarget);
	BackBuffer->Release();
}

Renderer::~Renderer()
{
	m_SwapChain->Release();
	m_ImmediateContext->Release();

	m_RenderTarget->Release();
}
