#include "Framework.h"
#include "PortalScene.h"
PortalScene::PortalScene()
{
	portal1 = new PortalQuad(Vector2(10,10));
	portal2 = new PortalQuad(Vector2(10,10));
	testQuad = new Quad();
	portal1->GetMaterial()->SetDiffuseMap(&p1Texture, L"Portal1");
	portal2->GetMaterial()->SetDiffuseMap(&p2Texture, L"Portal2");
	portal1->SetCamera(P2CAMERA);
	portal2->SetCamera(P1CAMERA);
	portal1->SetCameraDiffuse(L"Landscape/Fieldstone_DM.tga");
	portal1->translation = Vector3(-10, 0, 0);
	portal2->translation = Vector3(10, 0, 0);
	portal1->rotation = Vector3(0, -XM_PIDIV2, 0);
	portal2->rotation = Vector3(0, XM_PIDIV2, 0);
	Environment::GetInstance()->GetP1Camera()->rotation = Vector3(0, XM_PI, 0);
	Environment::GetInstance()->GetP2Camera()->rotation = Vector3(0, XM_PI, 0);

	cube = new TextureCube();
	mainCameraCube = new TextureCube;
	mainCameraCube->SetDiffuseMap(L"Landscape/Wall.png");
	ENVIRONMENT->GetP1Camera()->SetParent(portal2);
	ENVIRONMENT->GetP2Camera()->SetParent(portal1);
	terrain = new Terrain(L"HeightMap/HeightMap256.png");
	terrain->translation = Vector3(-100, 0, -100);

	terrain->GetMaterial()->SetDiffuseMap(L"Landscape/Dirt2.png");
	terrain->GetMaterial()->SetSpecularMap(L"Landscape/Wall_specular.png");
	terrain->GetMaterial()->SetNormalMap(L"Landscape/Wall_normal.png");
}

PortalScene::~PortalScene()
{
	delete portal1;
	delete portal2;
	delete cube;
	delete testQuad;
	delete terrain;
	delete mainCameraCube;
	
}

void PortalScene::Update()
{
	CalculateMirror();

	//P2CAMERA->SetWorld(p2CamTransform);
	//// 카메라가 포탈1을 바라볼 때, 포탈2의 뷰를 계산
	//Matrix p1CamTransform = mainCameraCube->GetWorld() * worldToPortal1;// *portal2ToWorld;
	//P1CAMERA->SetWorld(p1CamTransform);

	//// 카메라가 포탈2를 바라볼 때, 포탈1의 뷰를 계산
	//Matrix p2CamTransform = mainCameraCube->GetWorld() * worldToPortal2;// *portal1ToWorld;
	//P2CAMERA->SetWorld(p2CamTransform);
	//Matrix p1Transform = CAMERA->GetWorld() * XMMatrixInverse(nullptr, portal1->GetWorld());
	//Matrix p2Transform = CAMERA->GetWorld() * XMMatrixInverse(nullptr, portal2->GetWorld());
	//Matrix p1Transform = XMMatrixInverse(nullptr, CAMERA->GetWorld()) * XMMatrixInverse(nullptr, portal1->GetWorld());
	//Matrix p2Transform = CAMERA->GetWorld() * XMMatrixInverse(nullptr, portal2->GetWorld());
	//P1CAMERA->SetWorld(p1Transform);
	//P2CAMERA->SetWorld(p2Transform);
	//Vector3 rotation1 = CAMERA->rotation - portal2->rotation;
	//Vector3 rotation2 =  CAMERA->rotation - portal1->rotation;
	//float distance1 = Vector3(CAMERA->GetGlobalPosition() - portal2->GetGlobalPosition()).Length();
	//float distance2 = Vector3(CAMERA->GetGlobalPosition() - portal1->GetGlobalPosition()).Length();
	//P1CAMERA->translation = -rotation1.GetNormalized() * distance1;
	//P2CAMERA->translation = -rotation2.GetNormalized() * distance2;
	//P1CAMERA->rotation =  rotation1;
	//P2CAMERA->rotation =  rotation2;
	portal1->translation;
	portal1->Update();
	portal2->Update();
	cube->Update();
	testQuad->Update();
	terrain->Update();
	mainCameraCube->Update();

	//// 포탈1과 포탈2의 월드 변환 행렬을 가져옵니다.
	//Matrix portal1ToWorld = portal1->GetWorld();
	//Matrix portal2ToWorld = portal2->GetWorld();

	//// 월드에서 포탈1과 포탈2로의 역변환 행렬을 계산합니다.
	//Matrix worldToPortal1 = XMMatrixInverse(nullptr, portal1ToWorld);
	//Matrix worldToPortal2 = XMMatrixInverse(nullptr, portal2ToWorld);

	//// 메인 카메라의 월드 변환 행렬을 가져옵니다.
	//Matrix mainCameraWorld = mainCameraCube->GetWorld();

	//// 메인 카메라의 쿼터니언 회전을 계산합니다.
	//XMVECTOR mainCameraRot = XMQuaternionRotationMatrix(mainCameraWorld);

	//// 메인 카메라가 포탈1을 바라볼 때, 포탈2의 뷰를 계산합니다.
	//Matrix p1CamTransform = mainCameraWorld * worldToPortal1 * portal2ToWorld;
	//P1CAMERA->SetWorld(p1CamTransform);

	//// 메인 카메라가 포탈2를 바라볼 때, 포탈1의 뷰를 계산합니다.
	//Matrix p2CamTransform = mainCameraWorld * worldToPortal2 * portal1ToWorld;
	//P2CAMERA->SetWorld(p2CamTransform);

	//// 쿼터니언을 사용하여 포탈 카메라의 회전을 계산합니다.
	//XMVECTOR portal1Rot = XMQuaternionRotationMatrix(portal1ToWorld);
	//XMVECTOR portal2Rot = XMQuaternionRotationMatrix(portal2ToWorld);

	//XMVECTOR p1CameraRot = XMQuaternionMultiply(mainCameraRot, XMQuaternionInverse(portal1Rot));
	//XMVECTOR p2CameraRot = XMQuaternionMultiply(mainCameraRot, XMQuaternionInverse(portal2Rot));

	//// 쿼터니언 회전을 Matrix 형태로 변환하여 카메라에 적용합니다.
	//P1CAMERA->SetRotation(XMMatrixRotationQuaternion(p1CameraRot));
	//P2CAMERA->SetRotation(XMMatrixRotationQuaternion(p2CameraRot));
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
	Matrix p1CamTransform = mainCameraCube->GetWorld() * worldToPortal1;
	//Matrix p1CamTransform = CAMERA->GetWorld() * worldToPortal1;
	XMFLOAT4X4 fWorld1;

	XMStoreFloat4x4(&fWorld1, p1CamTransform);
	Vector3 p1Translation = Vector3(-fWorld1._41, fWorld1._42, -fWorld1._43);
	//Vector3 pos1 =     portal2->GetGlobalPosition();
	//Vector3 forward1 = portal2->GetForwardVector();
	//float A1 = forward1.x;
	//float B1 = forward1.y;
	//float C1 = forward1.z;
	//float D1 = -(A1 * pos1.x + B1 * pos1.y + C1 * pos1.z);
	//Vector3 p1FTrans;
	//p1FTrans.x = p1Translation.x - 2 * (A1 * p1Translation.x + B1 * p1Translation.y + C1 * p1Translation.z + D1) * A1;
	//p1FTrans.y = p1Translation.y - 2 * (A1 * p1Translation.x + B1 * p1Translation.y + C1 * p1Translation.z + D1) * B1;
	//p1FTrans.z = p1Translation.z - 2 * (A1 * p1Translation.x + B1 * p1Translation.y + C1 * p1Translation.z + D1) * C1;
	P1CAMERA->translation = p1Translation;
	//P1CAMERA->SetWorld(p1CamTransform);

	//Matrix p2CamTransform = CAMERA->GetWorld() * worldToPortal2;
	Matrix p2CamTransform = mainCameraCube->GetWorld() * worldToPortal2;

	XMFLOAT4X4 fWorld2;

	XMStoreFloat4x4(&fWorld2, p2CamTransform);
	Vector3 p2Translation = Vector3(-fWorld2._41, fWorld2._42, -fWorld2._43);
	//Vector3 pos2 =     portal1->GetGlobalPosition();
	//Vector3 forward2 = portal1->GetForwardVector();
	//float A2 = forward2.x;
	//float B2 = forward2.y;
	//float C2 = forward2.z;
	//float D2 = -(A2 * pos2.x + B2 * pos2.y + C2 * pos2.z);
	//Vector3 p2FTrans;
	//p2FTrans.x = p2Translation.x - 2 * (A2 * p2Translation.x + B2 * p2Translation.y + C2 * p2Translation.z + D2) * A2;
	//p2FTrans.y = p2Translation.y - 2 * (A2 * p2Translation.x + B2 * p2Translation.y + C2 * p2Translation.z + D2) * B2;
	//p2FTrans.z = p2Translation.z - 2 * (A2 * p2Translation.x + B2 * p2Translation.y + C2 * p2Translation.z + D2) * C2;
	P2CAMERA->translation = p2Translation;
}

void PortalScene::P1ReRender()
{
	portal1->Render();

}

void PortalScene::P2ReRender()
{

	portal2->Render();
	cube->Render();

}
