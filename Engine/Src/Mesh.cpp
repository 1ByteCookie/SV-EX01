#include "Mesh.hpp"

Mesh::Mesh(	ID3D11Buffer*						VertexBuffer,
			ID3D11Buffer*						IndexBuffer,
			ID3D11VertexShader*					VertexShader,
			ID3D11PixelShader*					PixelShader,
			ID3D11InputLayout*					Layout,
			const std::vector<unsigned int>&	Indices,
			UINT								Stride)
{
	m_VertexBuffer	= VertexBuffer;
	m_IndexBuffer	= IndexBuffer;
	m_VS			= VertexShader;
	m_PS			= PixelShader;
	m_Layout		= Layout;
	m_Indices		= Indices;
	m_Stride		= Stride;
}

Mesh::Mesh(Mesh&& Object) noexcept
{
	m_VertexBuffer	= Object.m_VertexBuffer;
	m_IndexBuffer	= Object.m_IndexBuffer;
	m_VS			= Object.m_VS;
	m_PS			= Object.m_PS;
	m_Layout		= Object.m_Layout;
	m_Indices		= Object.m_Indices;
	m_Stride		= Object.m_Stride;

	Object.m_VertexBuffer	= NULL;
	Object.m_IndexBuffer	= NULL;
	Object.m_VS				= NULL;
	Object.m_PS				= NULL;
	Object.m_Layout			= NULL;
	Object.m_Indices.clear();
	Object.m_Stride			= 0;
}

Mesh::~Mesh()
{
	if (m_VertexBuffer) { m_VertexBuffer->Release(); }
	if (m_IndexBuffer) { m_IndexBuffer->Release(); }
	
	if (m_VS) { m_VS->Release(); }
	if (m_PS) { m_PS->Release(); }
	
	if (m_Layout) { m_Layout->Release(); }
}
