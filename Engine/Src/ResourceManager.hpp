#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include "Mesh.hpp"

struct Vertex
{
	DirectX::XMFLOAT2 Position;
	DirectX::XMFLOAT4 Color;
};

struct cBuffer
{
	DirectX::XMMATRIX Model;
};

class ResourceManager
{
public:
	ResourceManager(ID3D11Device* Device);
	~ResourceManager();
	ResourceManager(const ResourceManager& Object) = delete;

	Mesh CreateMesh(const std::vector<Vertex>& Vertices,
					const std::vector<unsigned int>& Indices,
					const cBuffer& Constants,
					LPCWSTR VS,
					LPCWSTR PS);

private:
	ID3D11Device* m_Device;

	ID3D11Buffer* CreateVertexBuffer(const std::vector<Vertex>& Vertices);
	ID3D11Buffer* CreateIndexBuffer(const std::vector<unsigned int>& Indices);
	ID3D11Buffer* CreateConstantBuffer(const cBuffer& Constants);

	ID3D11VertexShader* CreateVS(LPCWSTR VS, ID3D11InputLayout** Layout);
	ID3D11PixelShader* CreatePS(LPCWSTR PS);
};