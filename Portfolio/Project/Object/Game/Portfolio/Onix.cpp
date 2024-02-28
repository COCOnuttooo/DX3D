#include "Framework.h"
#include "Onix.h"
Onix::Onix()
{
	parent = new Transform;
	texture = new ModelInstancing("Rock");
	for (int i = 0; i < 11; i++)
	{
		if (i !=0)
		{
			Vector3 dest = bodies[i - 1]->translation;
			dests.push_back(dest);
		}
		ColliderSphere* sphere = new ColliderSphere;
		sphere->translation.z = -i * 2;
		sphere->scale *= (1 - 0.08 * i);
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
}

void Onix::Update()
{

	//Input();
	BodyMove();
	//Stay();
	head->Update();
	for (auto& i : bodies)
	{
		i->Update();
	}
	texture->Update();
}

void Onix::Render()
{
	for (auto& i : bodies)
	{
		i->Render();
	}
	texture->Render();
	head->Render();
}
void Onix::SpinMove()
{
	
}
void Onix::Debug()
{
	head->Debug();
}


void Onix::BodyMove()
{
	//distanceBetweenBody = 2.0f;
	//// 첫 번째 링크의 움직임 (기존 구현 유지)
	////float speed = 3.0f; // 초당 이동 속도
	////bodies[0]->translation.z = 5 * sin(time);
	////bodies[0]->translation.y = 5 * cos(time);
	////bodies[0]->translation.x += speed * DELTA_TIME;
	time += DELTA_TIME;
	bodies[0]->rotation.y = time * 2;
	bodies[0]->rotation.x = time * 1;
	bodies[0]->rotation.z = time * 1;
	bodies[0]->translation += bodies[0]->GetForwardVector() * 10 * DELTA_TIME;

	// bodies[0]의 회전을 업데이트하여 원형 경로를 따라 이동
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
		Vector3 a = distance * Vector3(sin(cos(time) * (2 - i *0.8) * XM_PIDIV4 - XM_PIDIV2), 0, cos(cos(time) * XM_PIDIV4 * (2 - i * 0.8) - XM_PIDIV2)).GetNormalized();
		Vector3 direction = (targetPosition - currentPosition).GetNormalized(); // 목표 방향
		Vector3 newPosition = targetPosition - direction * distance; // 목표 위치에서 일정 거리 떨어진 위치 계산

		// newPosition을 사용하여 이동 처리
		bodies[i]->translation = bodies[i-1]->translation + a;
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
//void Onix::Move()
//{
//	distanceBetweenBody = 2.0f;
//	// 첫 번째 링크의 움직임을 멈춤 (머리 고정)
//	// time += DELTA_TIME; // 시간 증가는 나머지 링크들의 움직임에만 영향을 미침
//
//	// 첫 번째 링크(머리)의 위치를 고정
//	// bodies[0]->translation.z, y, x를 변경하지 않음
//
//	// 나머지 링크들의 움직임 업데이트
//	time += DELTA_TIME;
//	for (int i = 1; i < bodies.size(); i++)
//	{
//		Vector3 targetPosition = bodies[i - 1]->translation; // 목표 위치: 바로 앞 링크의 위치
//		Vector3 currentPosition = bodies[i]->translation; // 현재 위치
//
//		// 링크별로 시간 오프셋을 적용하여 자연스러운 움직임 생성
//		float localTimeOffset = i * 0.5f; // 링크마다 다른 시간 오프셋을 적용
//		float localTime = time + localTimeOffset; // 전역 시간에 오프셋 적용
//
//		// 거리를 유지하며 이동하기
//		float distance = bodies[i]->scale.x + bodies[i - 1]->scale.x;
//		Vector3 direction = (targetPosition - currentPosition).GetNormalized(); // 목표 방향
//		Vector3 dynamicOffset = Vector3(0, 0.5f * sin(localTime), 0.5f * cos(localTime)); // 시간에 따라 변하는 동적 오프셋
//		Vector3 newPosition = targetPosition - direction * distance + dynamicOffset; // 목표 위치에서 일정 거리 떨어진 위치에 동적 오프셋 적용
//
//		// newPosition을 사용하여 이동 처리
//		bodies[i]->translation = newPosition;
//	}
//}