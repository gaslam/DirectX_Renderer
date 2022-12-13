#pragma once
#include "DataTypes.h"
#include <vector>
class Effect;
class Mesh3D
{
public:
	Mesh3D(ID3D11Device* pDevice, std::vector<dae::Vertex>& vertices, std::vector<uint32_t>& indices);
	~Mesh3D();

	Mesh3D(const Mesh3D& other) = delete;
	Mesh3D(Mesh3D& other) noexcept = delete;
	Mesh3D& operator=(const Mesh3D& other) = delete;
	Mesh3D& operator=(Mesh3D&& other) noexcept = delete;

	void Render(ID3D11DeviceContext* pDeviceContext) const;
private:
	ID3D11Device* m_pDevice{ nullptr };
	ID3D11InputLayout* m_pInputLayout{ nullptr };
	ID3D11Buffer* m_pVertexBuffer{ nullptr };
	ID3D11Buffer* m_pIndexBuffer{ nullptr };

	uint32_t m_NumIndices;

	Effect* m_pEffect{nullptr};
};

