#include "Framework.h"
#include "PixelShader.h"

PixelShader::PixelShader(wstring file)
{
    //PixelShader
    {
        DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

        D3DCompileFromFile
        (
            file.c_str(),
            nullptr,
            nullptr,
            "PS", "ps_5_0",
            flags,
            0,
            &blob,
            nullptr
        );

        DEVICE->CreatePixelShader
        (
            blob->GetBufferPointer(),
            blob->GetBufferSize(),
            nullptr,
            &pixelShader
        );

    }
}

PixelShader::~PixelShader()
{
    pixelShader->Release();
}

void PixelShader::SetShader()
{
    DC->PSSetShader(pixelShader, nullptr, 0);
}
