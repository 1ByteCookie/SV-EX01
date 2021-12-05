#pragma once

#include <d3d11.h>
#include <vector>

class Mesh
{
public:
	Mesh(	ID3D11Buffer*						VertexBuffer,
			ID3D11Buffer*						IndexBuffer,
			ID3D11Buffer*						ConstantBuffer,
			ID3D11VertexShader*					VertexShader,
			ID3D11PixelShader*					PixelShader,
			ID3D11InputLayout*					Layout,
			const std::vector<unsigned int>&	Indices,
			UINT								Stride);
	
	
	Mesh(Mesh&& Object) noexcept;
	~Mesh();
	Mesh(const Mesh& Object) = delete;

	inline auto& GetVB() const { return m_VertexBuffer; }
	inline auto& GetIB() const { return m_IndexBuffer; }
	inline auto& GetCB() const { return m_ConstantBuffer; }
	inline auto& GetVS() const { return m_VS; }
	inline auto& GetPS() const { return m_PS; }
	inline auto& GetLayout() const { return m_Layout; }
	inline auto& GetIndices() const { return m_Indices; }
	inline auto& GetStride() const { return m_Stride; }

private:
	ID3D11Buffer*				m_VertexBuffer;
	ID3D11Buffer*				m_IndexBuffer;
	ID3D11Buffer*				m_ConstantBuffer;
	ID3D11VertexShader*			m_VS;
	ID3D11PixelShader*			m_PS;

	ID3D11InputLayout*			m_Layout;
	std::vector<unsigned int>	m_Indices;
	UINT						m_Stride;
};