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
	//ENVIRONMENT->GetP1Camera()->SetParent(portal2);
	//ENVIRONMENT->GetP2Camera()->SetParent(portal1);
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
	//Matrix portal1ToWorld = portal1->GetWorld();
	//Matrix portal2ToWorld = portal2->GetWorld();

	//Matrix worldToPortal1 = XMMatrixInverse(nullptr, portal1ToWorld);
	//Matrix worldToPortal2 = XMMatrixInverse(nullptr, portal2ToWorld);

	//// ī�޶� ��Ż1�� �ٶ� ��, ��Ż2�� �並 ���
	//Matrix p1CamTransform = mainCameraCube->GetWorld() * worldToPortal1;// *portal2ToWorld;
	//P1CAMERA->SetWorld(p1CamTransform);

	//// ī�޶� ��Ż2�� �ٶ� ��, ��Ż1�� �並 ���
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

	// ��Ż1�� ��Ż2�� ���� ��ȯ ����� �����ɴϴ�.
	Matrix portal1ToWorld = portal1->GetWorld();
	Matrix portal2ToWorld = portal2->GetWorld();

	// ���忡�� ��Ż1�� ��Ż2���� ����ȯ ����� ����մϴ�.
	Matrix worldToPortal1 = XMMatrixInverse(nullptr, portal1ToWorld);
	Matrix worldToPortal2 = XMMatrixInverse(nullptr, portal2ToWorld);

	// ���� ī�޶��� ���� ��ȯ ����� �����ɴϴ�.
	Matrix mainCameraWorld = mainCameraCube->GetWorld();

	// ���� ī�޶��� ���ʹϾ� ȸ���� ����մϴ�.
	XMVECTOR mainCameraRot = XMQuaternionRotationMatrix(mainCameraWorld);

	// ���� ī�޶� ��Ż1�� �ٶ� ��, ��Ż2�� �並 ����մϴ�.
	Matrix p1CamTransform = mainCameraWorld * worldToPortal1 * portal2ToWorld;
	P1CAMERA->SetWorld(p1CamTransform);

	// ���� ī�޶� ��Ż2�� �ٶ� ��, ��Ż1�� �並 ����մϴ�.
	Matrix p2CamTransform = mainCameraWorld * worldToPortal2 * portal1ToWorld;
	P2CAMERA->SetWorld(p2CamTransform);

	// ���ʹϾ��� ����Ͽ� ��Ż ī�޶��� ȸ���� ����մϴ�.
	XMVECTOR portal1Rot = XMQuaternionRotationMatrix(portal1ToWorld);
	XMVECTOR portal2Rot = XMQuaternionRotationMatrix(portal2ToWorld);

	XMVECTOR p1CameraRot = XMQuaternionMultiply(mainCameraRot, XMQuaternionInverse(portal1Rot));
	XMVECTOR p2CameraRot = XMQuaternionMultiply(mainCameraRot, XMQuaternionInverse(portal2Rot));

	// ���ʹϾ� ȸ���� Matrix ���·� ��ȯ�Ͽ� ī�޶� �����մϴ�.
	P1CAMERA->SetRotation(XMMatrixRotationQuaternion(p1CameraRot));
	P2CAMERA->SetRotation(XMMatrixRotationQuaternion(p2CameraRot));
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
}
