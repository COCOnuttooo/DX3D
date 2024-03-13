#include "Framework.h"
#include "Onix.h"
Onix::Onix()
{
	parent = new Transform;
	texture = new ModelInstancing("Rock");
	for (int i = 0; i < 11; i++)
	{
		if (i != 0)
		{
			Vector3 dest = bodies[i - 1]->translation;
			dests.push_back(dest);
		}
		ColliderSphere* sphere = new ColliderSphere;
		sphere->scale *= (1 - 0.08 * i);
		sphere->scale *= 5;
		sphere->translation.z = -i * 2 * sphere->scale.x;
		sphere->SetParent(parent);
		if (i == 0)
		{
			head = new Model("DragonHead");
			//head->rotation.y = -XM_PIDIV2;
			//head->scale *= 0.1;
			head->rotation.y = XM_PI;
			head->SetParent(sphere);

		}
		else
		{

			Transform* instance = texture->AddTransform();
			instance->SetParent(sphere);
			//instance->rotation.x = XM_PIDIV2;
			instance->rotation.y = XM_PI;

			instance->scale *= 0.7;
			instance->scale.y *= 0.5;
		}
		if (i != 0)
		{
			Vector3 source = sphere->translation;
			sources.push_back(source);
		}
		bodies.push_back(sphere);
	}
	SetDirection(Vector3(0, 10, 0));
	windEffect = new WindEffect(L"Effect/Snow.png", bodies[0], 5);
}

Onix::~Onix()
{
	for (auto& i : bodies)
	{
		delete i;
	}
	delete texture;
	delete head;
	delete parent;
	delete windEffect;
}

void Onix::Update()
{

	//Input();
	Pattern1();
	BodyMove();
	//if (bodies[0]->translation.y >= 20)
	//{
	//	SetDirection(target->GetGlobalPosition());
	//	moveSpeed = 10.0f;
	//}
	//Stay();
	head->Update();
	for (auto& i : bodies)
	{
		i->Update();
	}
	texture->Update();
	windEffect->Update();
}

void Onix::Render()
{
	//for (auto& i : bodies)
	//{
	//	i->Render();
	//}
	texture->Render();
	head->Render();
	windEffect->Render();
}
void Onix::SpinMove()
{

}
void Onix::Debug()
{
	head->Debug();
	if (ImGui::TreeNode("Onix"))
	{
		ImGui::Text("Pos :   %f,   %f,   %f", bodies[0]->rotation.x, bodies[0]->rotation.y, bodies[0]->rotation.z);

		ImGui::TreePop();
	}
}


void Onix::BodyMove()
{
	//distanceBetweenBody = 2.0f;
	//// 첫 번째 링크의 움직임 (기존 구현 유지)


	// 나머지 링크들의 움직임 업데이트
	for (int i = 1; i < bodies.size(); i++)
	{
		Vector3 targetPosition = bodies[i - 1]->translation; // 목표 위치: 바로 앞 링크의 위치
		Vector3 currentPosition = bodies[i]->translation; // 현재 위치

		// 거리를 유지하며 이동하기
		float distance = bodies[i]->scale.x + bodies[i - 1]->scale.x;
		Vector3 direction = (targetPosition - currentPosition).GetNormalized(); // 목표 방향
		Vector3 newPosition = targetPosition - direction * distance; // 목표 위치에서 일정 거리 떨어진 위치 계산

		// newPosition을 사용하여 이동 처리
		bodies[i]->rotation = bodies[i - 1]->rotation;
		bodies[i]->translation = newPosition;
	}

}
void Onix::Stay()
{
	distanceBetweenBody = 2.0f;
	// 첫 번째 링크의 움직임 (기존 구현 유지)
	time += DELTA_TIME;
	float speed = 3.0f; // 초당 이동 속도
	//bodies[1]->translation.x = 5 * sin(time);
	//bodies[1]->translation.z = 5 * cos(time);
	//Vector3 a = distanceBetweenBody * Vector3(sin(cos(time) * XM_PIDIV4 -XM_PIDIV2), 0, cos(cos(time) * XM_PIDIV4 - XM_PIDIV2));
	//bodies[1]->translation = bodies[0]->translation + a;
	//bodies[1]->translation.x += speed * DELTA_TIME;

	// 나머지 링크들의 움직임 업데이트
	for (int i = 1; i < bodies.size(); i++)
	{

		Vector3 targetPosition = bodies[i - 1]->translation; // 목표 위치: 바로 앞 링크의 위치
		Vector3 currentPosition = bodies[i]->translation; // 현재 위치

		// 거리를 유지하며 이동하기
		float distance = bodies[i]->scale.x + bodies[i - 1]->scale.x;
		Vector3 a = distance * Vector3(sin(cos(time) * (2 - i * 0.8) * XM_PIDIV4 - XM_PIDIV2), 0, cos(cos(time) * XM_PIDIV4 * (2 - i * 0.8) - XM_PIDIV2)).GetNormalized();
		Vector3 direction = (targetPosition - currentPosition).GetNormalized(); // 목표 방향
		Vector3 newPosition = targetPosition - direction * distance; // 목표 위치에서 일정 거리 떨어진 위치 계산

		// newPosition을 사용하여 이동 처리
		bodies[i]->translation = bodies[i - 1]->translation + a;
	}
}
void Onix::Input()
{
	if (KEY_PRESS('W'))
	{
		bodies[0]->translation += bodies[0]->GetForwardVector() * 3.0f * DELTA_TIME;
	}
	if (KEY_PRESS('A'))
	{
		bodies[0]->rotation.y -= 1 * DELTA_TIME;

	}
	if (KEY_PRESS('D'))
	{
		bodies[0]->rotation.y += 1 * DELTA_TIME;

	}
}
//void Onix::SetDirection(Vector3 dest)
//{
//	//dest = Vector3(1, 0, -10);
//	Vector3 dir = dest - bodies[0]->translation;
//	dir = dir.GetNormalized();
//	bodies[0]->rotation.y = atan2f(dir.z, dir.x);
//	float axisValue = sqrt(dir.z * dir.z + dir.x * dir.x);
//	bodies[0]->rotation.x = -atan2f(dir.y,axisValue );
//}
void Onix::SetDirection(Vector3 dest)
{
	Vector3 dir = dest - bodies[0]->translation;

	// 방향 벡터를 정규화
	dir = dir.GetNormalized();

	bodies[0]->rotation.y = atan2f(dir.x, dir.z);

	float axisValue = sqrt(dir.x * dir.x + dir.z * dir.z);
	bodies[0]->rotation.x = -atan2f(dir.y, axisValue);

}

void Onix::Pattern1()
{
	//if (state != ONIXIDLE)
	//{
	//	return;
	//}
	if (state == ONIXIDLE)
	{
		SetDirection(Vector3(bodies[0]->translation.x, bodies[0]->translation.y + 10, bodies[0]->translation.z));
		moveSpeed = 30.0f;

		state = PATTERN1;
	}
	if (bodies[0]->translation.y >= 100)
	{
		windEffect->PlayTargeted();
		windEffect->SetTailLength(0.8);

		SetDirection(target->translation);
		moveSpeed = 30.0f;
	}
	if (bodies[0]->translation.y < -100)
	{
		SetDirection(Vector3(bodies[0]->translation.x, bodies[0]->translation.y + 10, bodies[0]->translation.z));
		moveSpeed = 10.0f;
		windEffect->TurnOff();
	}
	bodies[0]->translation += bodies[0]->GetForwardVector() * moveSpeed * DELTA_TIME;
	Vector3 body1Dir = (bodies[0]->translation - bodies[1]->translation).GetNormalized();
	Vector3 body2Dir = (bodies[3]->translation - bodies[4]->translation).GetNormalized();
	Vector3 body3Dir = (bodies[5]->translation - bodies[6]->translation).GetNormalized();
	Vector3 body4Dir = (bodies[8]->translation - bodies[9]->translation).GetNormalized();
	float angle1 = Vector3(XMVector3Dot(body1Dir, bodies[0]->GetForwardVector())).x;
	float angle2 = Vector3(XMVector3Dot(body2Dir, bodies[0]->GetForwardVector())).x;
	float angle3 = Vector3(XMVector3Dot(body3Dir, bodies[0]->GetForwardVector())).x;
	float angle4 = Vector3(XMVector3Dot(body4Dir, bodies[0]->GetForwardVector())).x;

	if (angle1 > 0.9)
		windEffect->SetTailLength(2);
	if (angle2 > 0.9)
		windEffect->SetTailLength(3);
	if (angle3 > 0.9)
		windEffect->SetTailLength(4);
	if (angle4 > 0.9)
		windEffect->SetTailLength(5);

}

void Onix::Pattern2()
{
}
