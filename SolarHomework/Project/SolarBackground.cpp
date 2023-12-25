#include "Framework.h"
#include "SolarBackground.h"
SolarBackground::SolarBackground()
{
	background = new SolarBackgroundQuad;
	background->scale = { 1500*10,1000 * 10, 1};
	//background->SetParent(ENVIRONMENT->GetCamera());
	background->translation.z = 10000;
	background->GetMaterial()->SetDiffuseMap(L"SolarSystem/Universe3.jpg");
}

SolarBackground::~SolarBackground()
{
	delete background;
	
}

void SolarBackground::Render()
{
	ID3D11DepthStencilState* pOriginalDepthStencilState;
	UINT stencilRef;
	DC->OMGetDepthStencilState(&pOriginalDepthStencilState, &stencilRef);
	//////////////////////////////////////////////////////////////////////////////////
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = TRUE; // 깊이 버퍼 사용
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 모든 깊이 정보 쓰기
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL; // 배경을 뒤로

	ID3D11DepthStencilState* pDepthStencilStateForBackground;
	DEVICE->CreateDepthStencilState(&depthStencilDesc, &pDepthStencilStateForBackground);
	DC->OMSetDepthStencilState(pDepthStencilStateForBackground, 1);


	background->Render();

	////////////////////////////////////////////////////////////////////////////////
	DC->OMSetDepthStencilState(pOriginalDepthStencilState, stencilRef);
	if (pOriginalDepthStencilState)
		pOriginalDepthStencilState->Release();

}

void SolarBackground::Update()
{
	background->Update();
}

