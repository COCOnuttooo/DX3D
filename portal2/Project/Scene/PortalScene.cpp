#include "Framework.h"
#include "PortalScene.h"
PortalScene::PortalScene()
{
	portal1 = new PortalQuad(Vector2(5,10));
	portal2 = new PortalQuad(Vector2(5,10));
	testQuad = new Quad();
	portal1->GetMaterial()->SetDiffuseMap(&p1Texture, L"Portal1");
	portal2->GetMaterial()->SetDiffuseMap(&p2Texture, L"Portal2");
	portal1->SetCamera(P2CAMERA);
	portal2->SetCamera(P1CAMERA);
	portal1->SetCameraDiffuse(L"Landscape/Fieldstone_DM.tga");
	portal1->translation = Vector3(-10, 5, 0);
	portal2->translation = Vector3(10, 5, 0);
	portal1->rotation = Vector3(0, -2*XM_PIDIV4, 0);
	portal2->rotation = Vector3(0, XM_PIDIV2, 0);
	Environment::GetInstance()->GetP1Camera()->rotation = Vector3(0, XM_PI, 0);
	Environment::GetInstance()->GetP2Camera()->rotation = Vector3(0, XM_PI, 0);
	
	cube = new TextureCube();
	// cube->translation.y = -5;
	mainCameraCube = new TextureCube;
	mainCameraCubeHead = new TextureCube;
	mainCameraCubeHead->SetParent(mainCameraCube);
	mainCameraCubeHead->translation = Vector3(0, 0, 0.5);
	mainCameraCubeHead->scale = Vector3(0.5, 0.5, 0.5);
	mainCameraCube->SetDiffuseMap(L"Landscape/Wall.png");
	ENVIRONMENT->GetP1Camera()->SetParent(portal2);
	ENVIRONMENT->GetP2Camera()->SetParent(portal1);
	terrain = new Terrain(L"HeightMap/HeightMap256.png");
	terrain->translation = Vector3(-100, 0, -100);

	terrain->GetMaterial()->SetDiffuseMap(L"Landscape/Dirt2.png");
	terrain->GetMaterial()->SetSpecularMap(L"Landscape/Wall_specular.png");
	terrain->GetMaterial()->SetNormalMap(L"Landscape/Wall_normal.png");
	/*CAMERA->SetParent(mainCameraCube);
	CAMERA->rotation = Vector3(0, 0, 0);*/
}

PortalScene::~PortalScene()
{
	delete portal1;
	delete portal2;
	delete cube;
	delete testQuad;
	delete terrain;
	delete mainCameraCube;
	delete mainCameraCubeHead;
	
}

void PortalScene::Update()
{
	//BoxMove();

	portal1->translation;
	portal1->Update();
	portal2->Update();
	cube->Update();
	testQuad->Update();
	terrain->Update();
	mainCameraCube->Update();
	mainCameraCubeHead->Update();
	CalculateMirror();
	//if (mainCameraCube->translation.x <  portal1->translation.x)
	//{
	//	mainCameraCube->translation.x = portal2->translation.x;
	//}
	//if (mainCameraCube->translation.x > portal2->translation.x)
	//{
	//	mainCameraCube->translation.x = portal1->translation.x;

	//}
	if (CAMERA->translation.x < portal1->translation.x)
	{
		CAMERA->translation.x = portal2->translation.x;
	}
	if (CAMERA->translation.x > portal2->translation.x)
	{
		CAMERA->translation.x = portal1->translation.x;
	}
}

void PortalScene::PreRender()
{
	cube->Render();
	//terrain->Render();
	//portal1->Render();
	//portal2->Render();
}

void PortalScene::Render()
{
	//terrain->Render();
	cube->Render();
	portal1->Render();
	portal2->Render();
	mainCameraCube->Render();
	mainCameraCubeHead->Render();
}

void PortalScene::PostRender()
{
	cube->Debug();
	mainCameraCube->Debug();
	P1CAMERA->Debug();
	P2CAMERA->Debug();
}

void PortalScene::CalculateMirror()
{
	Matrix portal1ToWorld = portal1->GetWorld();
	Matrix portal2ToWorld = portal2->GetWorld();

	Matrix worldToPortal1 = XMMatrixInverse(nullptr, portal1ToWorld);
	Matrix worldToPortal2 = XMMatrixInverse(nullptr, portal2ToWorld);
	//Matrix p1CamTransform = mainCameraCube->GetWorld() * worldToPortal1;
	//Matrix p2CamTransform = mainCameraCube->GetWorld() * worldToPortal2;
	Matrix p1CamTransform = CAMERA->GetWorld() * worldToPortal1;
	Matrix p2CamTransform = CAMERA->GetWorld() * worldToPortal2;
	XMFLOAT4X4 fWorld1;

	XMStoreFloat4x4(&fWorld1, p1CamTransform);
	Vector3 p1Translation = Vector3(fWorld1._41, fWorld1._42, -fWorld1._43);

	P1CAMERA->translation = p1Translation;


	XMFLOAT4X4 fWorld2;

	XMStoreFloat4x4(&fWorld2, p2CamTransform);
	Vector3 p2Translation = Vector3(fWorld2._41, fWorld2._42, -fWorld2._43);

	P2CAMERA->translation = p2Translation;
	
	//Vector3 p1Rotation = mainCameraCube->rotation - portal1->rotation;
	//Vector3 p2Rotation = mainCameraCube->rotation - portal2->rotation;
	//P1CAMERA->rotation = Vector3(p1Rotation.x, p1Rotation.y + XM_PI, p1Rotation.z);
	//P2CAMERA->rotation = Vector3(p2Rotation.x, p2Rotation.y + XM_PI, p2Rotation.z);

	XMVECTOR cameraPosition1 = XMVectorSet(P1CAMERA->translation.x, P1CAMERA->translation.y, P1CAMERA->translation.z, 0); // 카메라 위치
	XMVECTOR cameraPosition2 = XMVectorSet(P2CAMERA->translation.x, P2CAMERA->translation.y, P2CAMERA->translation.z, 0); // 카메라 위치
	XMVECTOR portalPosition1 = XMVectorSet(0, 0, 0, 0); // 포탈 위치
	XMVECTOR portalPosition2 = XMVectorSet(0, 0, 0, 0); // 포탈 위치
	
	XMVECTOR upDirection1 = portal2->GetUpVector();
	XMVECTOR upDirection2 = portal1->GetUpVector();

	//XMVECTOR upDirection1 = P1CAMERA->GetUpVector();
	//XMVECTOR upDirection2 = P2CAMERA->GetUpVector();
	//invertsPortalView;
	Matrix p1Inverse = XMMatrixInverse(nullptr, XMMatrixRotationRollPitchYaw(portal2->rotation.x, portal2->rotation.y, portal2->rotation.z));
	Matrix p2Inverse = XMMatrixInverse(nullptr, XMMatrixRotationRollPitchYaw(portal1->rotation.x, portal1->rotation.y, portal1->rotation.z));
	 //'Look At' 뷰 행렬 생성
	XMMATRIX viewMatrix1;
	XMMATRIX viewMatrix2;
	float distanceP1 = max(0.1,P1CAMERA->translation.Length());
	float distanceP2 = max(0.1,P2CAMERA->translation.Length());
	float fov1 = 2 * atanf(0.5 * portal2->GetSize().x / distanceP1);
	float fov2 = 2 * atanf(0.5 * portal1->GetSize().x / distanceP2);
	if (P1CAMERA->translation.Length() != 0)
	{
		//viewMatrix1 = XMMatrixLookToLH(cameraPosition1, -cameraPosition1, upDirection1);
		//P1CAMERA->SetFixViewMatrix(viewMatrix1);

		//persP1 = XMMatrixPerspectiveOffCenterLH(-2.5, 2.5, -2.5, 2.5, distanceP1, 1000);
		viewMatrix1 = XMMatrixInverse(nullptr,XMMatrixLookAtLH(cameraPosition1, portalPosition1, upDirection1));// *p1Inverse;
		
		persP1 = viewMatrix1*  XMMatrixPerspectiveFovLH(fov1, WIN_WIDTH / WIN_HEIGHT * portal2->GetSize().x / portal2->GetSize().y, distanceP1, 1000) ;
	}
	else { P1CAMERA->SetFixViewMatrix(XMMatrixIdentity()); }
	if (P2CAMERA->translation.Length()!= 0)
	{
		viewMatrix2 = XMMatrixInverse(nullptr,XMMatrixLookAtLH(cameraPosition2, portalPosition2, upDirection2));// *p2Inverse;
		//viewMatrix2 = XMMatrixLookToLH(cameraPosition2, -cameraPosition2, upDirection1);

		//P2CAMERA->SetFixViewMatrix(viewMatrix2);
		//persP2 = XMMatrixPerspectiveOffCenterLH(-2.5, 2.5, -2.5, 2.5, distanceP2, 1000);
		persP2 = viewMatrix2* XMMatrixPerspectiveFovLH(fov2, WIN_WIDTH / WIN_HEIGHT * portal1->GetSize().x / portal1->GetSize().y, distanceP2, 1000);

	}
	else { P2CAMERA->SetFixViewMatrix(XMMatrixIdentity()); }

	//P1CAMERA->SetFixViewMatrix(XMMatrixIdentity());
	//P2CAMERA->SetFixViewMatrix(XMMatrixIdentity());

}

void PortalScene::P1ReRender()
{
	portal1->Render();

}

void PortalScene::P2ReRender()
{

	portal2->Render();

}

XMFLOAT3 PortalScene::ExtractEulerAnglesFromMatrix(const XMMATRIX& mat)
{

	XMFLOAT4X4 fMat;
	XMStoreFloat4x4(&fMat, mat);  // XMMATRIX를 XMFLOAT4X4로 변환

	XMFLOAT3 angles;

	// 피치 각도
	angles.x = asin(-fMat._32);  // fMat._32는 행렬의 3번째 열, 2번째 행

	// 요 각도
	if (cos(angles.x) > 0.0001) {
		angles.y = atan2(fMat._31, fMat._33);  // fMat._31과 fMat._33를 사용하여 계산
		angles.z = atan2(fMat._12, fMat._22);  // fMat._12와 fMat._22를 사용하여 계산
	}
	else {
		// 짐벌 락 처리
		angles.y = atan2(-fMat._21, fMat._11);  // fMat._21과 fMat._11를 사용하여 계산
		angles.z = 0.0f;
	}

	return angles;
}

void PortalScene::BoxMove()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('A'))
		{
			mainCameraCube->translation += -mainCameraCube->GetRightVector() * moveSpeed * DELTA_TIME;
		}

		if (KEY_PRESS('D'))
		{
			mainCameraCube->translation += +mainCameraCube->GetRightVector() * moveSpeed * DELTA_TIME;
		}

		if (KEY_PRESS('Q'))
		{
			mainCameraCube->translation += -mainCameraCube->GetUpVector() * moveSpeed * DELTA_TIME;
		}

		if (KEY_PRESS('E'))
		{
			mainCameraCube->translation += +mainCameraCube->GetUpVector() * moveSpeed * DELTA_TIME;
		}
		if (KEY_PRESS('S'))
		{
			mainCameraCube->translation += -mainCameraCube->GetForwardVector() * moveSpeed * DELTA_TIME;
		}

		if (KEY_PRESS('W'))
		{
			mainCameraCube->translation += +mainCameraCube->GetForwardVector() * moveSpeed * DELTA_TIME;
		}
		Vector3 delta = mousePos - oldPos;

		mainCameraCube->rotation.y -= delta.x * rotateSpeed;// * DELTA_TIME;
		mainCameraCube->rotation.x -= delta.y * rotateSpeed;// * DELTA_TIME;
	}

	
	oldPos = mousePos;
}
