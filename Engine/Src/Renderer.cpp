#include "Renderer.hpp"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>

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

	DrawInit();
}

Renderer::~Renderer()
{
	m_SwapChain->Release();
	m_ImmediateContext->Release();

	m_RenderTarget->Release();
}

struct Vertex
{
	DirectX::XMFLOAT2 Positions;
};

void Renderer::DrawInit()
{
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

	D3D11_BUFFER_DESC vbDescriptor{};
	vbDescriptor.ByteWidth				= sizeof(Vertex) * Vertices.size();
	vbDescriptor.Usage					= D3D11_USAGE_DEFAULT;
	vbDescriptor.BindFlags				= D3D11_BIND_VERTEX_BUFFER;
	vbDescriptor.CPUAccessFlags			= 0;
	vbDescriptor.StructureByteStride	= sizeof(Vertex);

	D3D11_BUFFER_DESC ibDescriptor{};
	ibDescriptor.ByteWidth				= sizeof(unsigned int) * Indices.size();
	ibDescriptor.Usage					= D3D11_USAGE_DEFAULT;
	ibDescriptor.BindFlags				= D3D11_BIND_INDEX_BUFFER;
	ibDescriptor.CPUAccessFlags			= 0;
	ibDescriptor.StructureByteStride	= sizeof(unsigned int);

	D3D11_SUBRESOURCE_DATA vbResource{};
	vbResource.pSysMem				= Vertices.data();
	vbResource.SysMemPitch			= 0;
	vbResource.SysMemSlicePitch		= 0;

	D3D11_SUBRESOURCE_DATA ibResource{};
	ibResource.pSysMem				= Indices.data();
	ibResource.SysMemPitch			= 0;
	ibResource.SysMemSlicePitch		= 0;

	m_Device->CreateBuffer(&vbDescriptor, &vbResource, &m_VertexBuffer);
	m_Device->CreateBuffer(&ibDescriptor, &ibResource, &m_IndexBuffer);

	//=================================

	ID3DBlob* Blob;
	
	D3DReadFileToBlob(L"ShaderBin/VertexShader.cso", &Blob);
	m_Device->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), NULL, &m_VS);

	D3D11_INPUT_ELEMENT_DESC ieDescriptor[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(Vertex, Vertex::Positions), D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	ID3D11InputLayout* Layout;
	m_Device->CreateInputLayout(ieDescriptor, 1, Blob->GetBufferPointer(), Blob->GetBufferSize(), &Layout);
	Blob->Release();

	D3DReadFileToBlob(L"ShaderBin/PixelShader.cso", &Blob);
	m_Device->CreatePixelShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), NULL, &m_PS);
	Blob->Release();
	
	//=================================

	m_ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_ImmediateContext->IASetInputLayout(Layout);

	UINT Stride = sizeof(Vertex), Offset = 0;
	m_ImmediateContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &Stride, &Offset);
	m_ImmediateContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	m_ImmediateContext->VSSetShader(m_VS, NULL, NULL);
	m_ImmediateContext->PSSetShader(m_PS, NULL, NULL);

	D3D11_VIEWPORT vDescriptor{};
	vDescriptor.Width		= 1280;
	vDescriptor.Height		= 720;
	vDescriptor.MaxDepth	= 0;
	vDescriptor.MinDepth	= 0;
	vDescriptor.TopLeftX	= 0;
	vDescriptor.TopLeftY	= 0;

	m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTarget, NULL);
	m_ImmediateContext->RSSetViewports(1, &vDescriptor);
	//=================================
}

void Renderer::Draw()
{
	m_ImmediateContext->DrawIndexed(3, 0, 0);
}