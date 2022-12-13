#pragma once
class Effect final
{
public:
	Effect(ID3D11Device* device, const std::wstring& assetFile);
	~Effect();

	Effect(const Effect& other) = delete;
	Effect(Effect&& other) = delete;
	Effect& operator=(const Effect& other) = delete;
	Effect& operator=(Effect&& other) = delete;

	static ID3DX11Effect* LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile);
	void LoadTechnique();

	ID3DX11Effect* GetEffect() const { return m_pEffect; }
	ID3DX11EffectTechnique* GetTechnique() const { return m_pTechnique; }
private:
	ID3DX11Effect* m_pEffect{nullptr};
	ID3DX11EffectTechnique* m_pTechnique{nullptr};
	ID3D11InputLayout* m_pInputLayout{ nullptr };
};

