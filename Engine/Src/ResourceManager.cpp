#include "ResourceManager.hpp"

#include <d3dcompiler.h>

ResourceManager::ResourceManager(ID3D11Device* Device)
	:m_Device(Device)
{

}

ResourceManager::~ResourceManager()
{
	m_Device->Release();
}

Mesh ResourceManager::CreateMesh(const std::vector<Vertex>& Vertices,
								 const std::vector<unsigned int>& Indices,
								 LPCWSTR VS,
								 LPCWSTR PS)
{
	ID3D11InputLayout* Layout = NULL;

	ID3D11Buffer* VertexBuffer	= CreateVertexBuffer(Vertices);
	ID3D11Buffer* IndexBuffer	= CreateIndexBuffer(Indices);
	ID3D11VertexShader* VShader = CreateVS(VS, &Layout);
	ID3D11PixelShader* PShader	= CreatePS(PS);

	return Mesh(VertexBuffer, IndexBuffer, VShader, PShader, Layout, Indices, sizeof(Vertex));
}

ID3D11Buffer* ResourceManager::CreateVertexBuffer(const std::vector<Vertex>& Vertices)
{
	D3D11_BUFFER_DESC vbDescriptor{};
	vbDescriptor.ByteWidth				= sizeof(Vertex) * Vertices.size();
	vbDescriptor.Usage					= D3D11_USAGE_DEFAULT;
	vbDescriptor.BindFlags				= D3D11_BIND_VERTEX_BUFFER;
	vbDescriptor.CPUAccessFlags			= 0;
	vbDescriptor.StructureByteStride	= sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA vbResource{};
	vbResource.pSysMem				= Vertices.data();
	vbResource.SysMemPitch			= 0;
	vbResource.SysMemSlicePitch		= 0;

	ID3D11Buffer* VertexBuffer = NULL;
	m_Device->CreateBuffer(&vbDescriptor, &vbResource, &VertexBuffer);

	return VertexBuffer;
}

ID3D11Buffer* ResourceManager::CreateIndexBuffer(const std::vector<unsigned int>& Indices)
{
	D3D11_BUFFER_DESC ibDescriptor{};
	ibDescriptor.ByteWidth				= sizeof(unsigned int) * Indices.size();
	ibDescriptor.Usage					= D3D11_USAGE_DEFAULT;
	ibDescriptor.BindFlags				= D3D11_BIND_INDEX_BUFFER;
	ibDescriptor.CPUAccessFlags			= 0;
	ibDescriptor.StructureByteStride	= sizeof(unsigned int);

	D3D11_SUBRESOURCE_DATA ibResource{};
	ibResource.pSysMem				= Indices.data();
	ibResource.SysMemPitch			= 0;
	ibResource.SysMemSlicePitch		= 0;

	ID3D11Buffer* IndexBuffer = NULL;
	m_Device->CreateBuffer(&ibDescriptor, &ibResource, &IndexBuffer);

	return IndexBuffer;
}

ID3D11VertexShader* ResourceManager::CreateVS(LPCWSTR VS, ID3D11InputLayout** Layout)
{
	ID3DBlob* Blob = NULL;
	ID3D11VertexShader* VShader;

	D3D11_INPUT_ELEMENT_DESC ieDescriptor[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(Vertex, Vertex::Position), D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, Vertex::Color), D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	D3DReadFileToBlob(VS, &Blob);
	m_Device->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), NULL, &VShader);
	m_Device->CreateInputLayout(ieDescriptor, 2, Blob->GetBufferPointer(), Blob->GetBufferSize(), Layout);

	Blob->Release();
	return VShader;
}

ID3D11PixelShader* ResourceManager::CreatePS(LPCWSTR PS)
{
	ID3DBlob* Blob = NULL;
	ID3D11PixelShader* PShader;

	D3DReadFileToBlob(PS, &Blob);
	m_Device->CreatePixelShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), NULL, &PShader);

	Blob->Release();
	return PShader;
}