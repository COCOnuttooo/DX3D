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
	//// ù ��° ��ũ�� ������ (���� ���� ����)
	////float speed = 3.0f; // �ʴ� �̵� �ӵ�
	////bodies[0]->translation.z = 5 * sin(time);
	////bodies[0]->translation.y = 5 * cos(time);
	////bodies[0]->translation.x += speed * DELTA_TIME;
	time += DELTA_TIME;
	bodies[0]->rotation.y = time * 2;
	bodies[0]->rotation.x = time * 1;
	bodies[0]->rotation.z = time * 1;
	bodies[0]->translation += bodies[0]->GetForwardVector() * 10 * DELTA_TIME;

	// bodies[0]�� ȸ���� ������Ʈ�Ͽ� ���� ��θ� ���� �̵�
	// ������ ��ũ���� ������ ������Ʈ
	for (int i = 1; i < bodies.size(); i++)
	{
		Vector3 targetPosition = bodies[i - 1]->translation; // ��ǥ ��ġ: �ٷ� �� ��ũ�� ��ġ
		Vector3 currentPosition = bodies[i]->translation; // ���� ��ġ

		// �Ÿ��� �����ϸ� �̵��ϱ�
		float distance = bodies[i]->scale.x + bodies[i - 1]->scale.x;
		Vector3 direction = (targetPosition - currentPosition).GetNormalized(); // ��ǥ ����
		Vector3 newPosition = targetPosition - direction * distance; // ��ǥ ��ġ���� ���� �Ÿ� ������ ��ġ ���

		// newPosition�� ����Ͽ� �̵� ó��
		bodies[i]->rotation = bodies[i - 1]->rotation;
		bodies[i]->translation = newPosition;
	}

}
void Onix::Stay()
{
	distanceBetweenBody = 2.0f;
	// ù ��° ��ũ�� ������ (���� ���� ����)
	time += DELTA_TIME;
	float speed = 3.0f; // �ʴ� �̵� �ӵ�
	//bodies[1]->translation.x = 5 * sin(time);
	//bodies[1]->translation.z = 5 * cos(time);
	//Vector3 a = distanceBetweenBody * Vector3(sin(cos(time) * XM_PIDIV4 -XM_PIDIV2), 0, cos(cos(time) * XM_PIDIV4 - XM_PIDIV2));
	//bodies[1]->translation = bodies[0]->translation + a;
	//bodies[1]->translation.x += speed * DELTA_TIME;

	// ������ ��ũ���� ������ ������Ʈ
	for (int i = 1; i < bodies.size(); i++)
	{

		Vector3 targetPosition = bodies[i - 1]->translation; // ��ǥ ��ġ: �ٷ� �� ��ũ�� ��ġ
		Vector3 currentPosition = bodies[i]->translation; // ���� ��ġ

		// �Ÿ��� �����ϸ� �̵��ϱ�
		float distance = bodies[i]->scale.x + bodies[i - 1]->scale.x;
		Vector3 a = distance * Vector3(sin(cos(time) * (2 - i *0.8) * XM_PIDIV4 - XM_PIDIV2), 0, cos(cos(time) * XM_PIDIV4 * (2 - i * 0.8) - XM_PIDIV2)).GetNormalized();
		Vector3 direction = (targetPosition - currentPosition).GetNormalized(); // ��ǥ ����
		Vector3 newPosition = targetPosition - direction * distance; // ��ǥ ��ġ���� ���� �Ÿ� ������ ��ġ ���

		// newPosition�� ����Ͽ� �̵� ó��
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
//	// ù ��° ��ũ�� �������� ���� (�Ӹ� ����)
//	// time += DELTA_TIME; // �ð� ������ ������ ��ũ���� �����ӿ��� ������ ��ħ
//
//	// ù ��° ��ũ(�Ӹ�)�� ��ġ�� ����
//	// bodies[0]->translation.z, y, x�� �������� ����
//
//	// ������ ��ũ���� ������ ������Ʈ
//	time += DELTA_TIME;
//	for (int i = 1; i < bodies.size(); i++)
//	{
//		Vector3 targetPosition = bodies[i - 1]->translation; // ��ǥ ��ġ: �ٷ� �� ��ũ�� ��ġ
//		Vector3 currentPosition = bodies[i]->translation; // ���� ��ġ
//
//		// ��ũ���� �ð� �������� �����Ͽ� �ڿ������� ������ ����
//		float localTimeOffset = i * 0.5f; // ��ũ���� �ٸ� �ð� �������� ����
//		float localTime = time + localTimeOffset; // ���� �ð��� ������ ����
//
//		// �Ÿ��� �����ϸ� �̵��ϱ�
//		float distance = bodies[i]->scale.x + bodies[i - 1]->scale.x;
//		Vector3 direction = (targetPosition - currentPosition).GetNormalized(); // ��ǥ ����
//		Vector3 dynamicOffset = Vector3(0, 0.5f * sin(localTime), 0.5f * cos(localTime)); // �ð��� ���� ���ϴ� ���� ������
//		Vector3 newPosition = targetPosition - direction * distance + dynamicOffset; // ��ǥ ��ġ���� ���� �Ÿ� ������ ��ġ�� ���� ������ ����
//
//		// newPosition�� ����Ͽ� �̵� ó��
//		bodies[i]->translation = newPosition;
//	}
//}