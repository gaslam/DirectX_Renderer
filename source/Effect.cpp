#include "pch.h"
#include "Effect.h"

Effect::Effect(ID3D11Device* pDevice, const std::wstring& assetFile)
{
    m_pEffect = LoadEffect(pDevice, assetFile);
    if (m_pEffect != nullptr)
    {
        LoadTechnique();
    }
}

ID3DX11Effect* Effect::LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile)
{
    HRESULT result;
    ID3D10Blob* pErrorBlob{ nullptr };
    ID3DX11Effect* pEffect;

    DWORD shaderFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
    shaderFlags |= D3DCOMPILE_DEBUG;
    shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    result = D3DX11CompileEffectFromFile(assetFile.c_str(),
        nullptr,
        nullptr,
        shaderFlags,
        0,
        pDevice,
        &pEffect,
        &pErrorBlob);

    if (FAILED(result))
    {
        if (pErrorBlob != nullptr)
        {
            const char* pErrors = static_cast<char*>(pErrorBlob->GetBufferPointer());

            std::wstringstream ss;

            for (unsigned int i = 0; i < pErrorBlob->GetBufferSize(); ++i)
            {
                ss << pErrors[i];
            }

            OutputDebugStringW(ss.str().c_str());
            pErrorBlob->Release();
            pErrorBlob = nullptr;

            std::wcout << ss.str() << std::endl;
        }
        else
        {
            std::wstringstream ss;
            ss << "EffectLoader: Failed to create effect from file!\nPath: " << assetFile;
            std::wcout << ss.str() << std::endl;
            return nullptr;
        }
    }

    return pEffect;
}

void Effect::LoadTechnique()
{
    m_pTechnique = m_pEffect->GetTechniqueByName("DefaultTechnique");

    if (!m_pTechnique->IsValid())
    {
        std::wcout << L"Technique is not valid\n";
    }
}

Effect::~Effect()
{
    if (m_pEffect)
    {
        m_pEffect->Release();
    }

    if (m_pTechnique)
    {
        m_pTechnique->Release();
    }
}
