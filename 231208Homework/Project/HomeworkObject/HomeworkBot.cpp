#include "Framework.h"
#include "HomeworkBot.h"
HomeworkBot::HomeworkBot()
{
	Initialize();
}

HomeworkBot::~HomeworkBot()
{
	for (pair<string,Cube*> i : robot)
		delete i.second;
	robot.clear();
}

void HomeworkBot::Initialize()
{
	robot.emplace("Body", new Cube(Vector4(0.5, 0.5, 0.5, 1)));
	robot["Body"]->scale.x = 0.8;
	robot["Body"]->scale.z = 0.6;
	robot.emplace("LArm", new Cube(Vector4(0.6,0.6,0.6,1)));
	robot["LArm"]->scale.x = 0.2;
	robot["LArm"]->scale.y = 0.5;
	robot["LArm"]->scale.z = 0.2;
	robot["LArm"]->translation.x = 0.5 * robot["Body"]->scale.x + 0.5* robot["LArm"]->scale.x;
	robot["LArm"]->SetPivot(Vector3(0, 0.5, 0));
	robot["LArm"]->SetParent(robot["Body"]);

	robot.emplace("LFArm", new Cube(Vector4(0.65, 0.65, 0.65, 1)));
	robot["LFArm"]->scale.x = 0.2;
	robot["LFArm"]->scale.y = 0.5;
	robot["LFArm"]->scale.z = 0.2;

	robot["LFArm"]->translation.y = -0.5 * robot["LArm"]->scale.y - 0.5* robot["LFArm"]->scale.y;
	robot["LFArm"]->SetPivot(Vector3(0, 0.5, 0));
	robot["LFArm"]->SetParent(robot["LArm"]);

	robot.emplace("RArm", new Cube(Vector4(0.6, 0.6, 0.6, 1)));
	robot["RArm"]->scale.x = 0.2;
	robot["RArm"]->scale.y = 0.5;
	robot["RArm"]->scale.z = 0.2;
	robot["RArm"]->translation.x = -0.5 * robot["Body"]->scale.x - 0.5 * robot["RArm"]->scale.x;
	robot["RArm"]->SetPivot(Vector3(0, 0.5, 0));
	robot["RArm"]->SetParent(robot["Body"]);

	robot.emplace("RFArm", new Cube(Vector4(0.65, 0.65, 0.65, 1)));
	robot["RFArm"]->scale.x = 0.2;
	robot["RFArm"]->scale.y = 0.5;
	robot["RFArm"]->scale.z = 0.2;
	robot["RFArm"]->translation.y = -0.5 * robot["RArm"]->scale.y - 0.5 * robot["RFArm"]->scale.y;
	robot["RFArm"]->SetPivot(Vector3(0, 0.5, 0));
	robot["RFArm"]->SetParent(robot["RArm"]);

	robot.emplace("LLeg", new Cube(Vector4(0.3, 0.3, 0.3, 1)));
	robot["LLeg"]->scale.x = 0.3;
	robot["LLeg"]->scale.y = 0.6;
	robot["LLeg"]->scale.z = 0.3;
	robot["LLeg"]->translation.y = -0.5 * robot["Body"]->scale.y - 0.5 * robot["LLeg"]->scale.y;
	robot["LLeg"]->translation.x = 0.24;
	robot["LLeg"]->SetPivot(Vector3(0, 0.5, 0));
	robot["LLeg"]->SetParent(robot["Body"]);

	robot.emplace("LFLeg", new Cube(Vector4(0.4, 0.4, 0.4, 1)));
	robot["LFLeg"]->scale.x = 0.3;
	robot["LFLeg"]->scale.y = 0.6;
	robot["LFLeg"]->scale.z = 0.3;
	robot["LFLeg"]->translation.y = -0.5 * robot["LFLeg"]->scale.y - 0.5 * robot["LLeg"]->scale.y;
	robot["LFLeg"]->SetPivot(Vector3(0, 0.5, 0));
	robot["LFLeg"]->SetParent(robot["LLeg"]);

	robot.emplace("RLeg", new Cube(Vector4(0.3, 0.3, 0.3, 1)));
	robot["RLeg"]->scale.x = 0.3;
	robot["RLeg"]->scale.y = 0.6;
	robot["RLeg"]->scale.z = 0.3;
	robot["RLeg"]->translation.y = -0.5 * robot["Body"]->scale.y - 0.5 * robot["RLeg"]->scale.y;
	robot["RLeg"]->translation.x = -0.24;
	robot["RLeg"]->SetPivot(Vector3(0, 0.5, 0));
	robot["RLeg"]->SetParent(robot["Body"]);

	robot.emplace("RFLeg", new Cube(Vector4(0.4, 0.4, 0.4, 1)));
	robot["RFLeg"]->scale.x = 0.3;
	robot["RFLeg"]->scale.y = 0.6;
	robot["RFLeg"]->scale.z = 0.3;
	robot["RFLeg"]->translation.y = -0.5 * robot["RFLeg"]->scale.y - 0.5 * robot["RLeg"]->scale.y;
	robot["RFLeg"]->SetPivot(Vector3(0, 0.5, 0));
	robot["RFLeg"]->SetParent(robot["RLeg"]);

	robot.emplace("Head", new Cube(Vector4(0.7, 0.5, 0.1, 1)));
	robot["Head"]->scale.x = 0.5;
	robot["Head"]->scale.y = 0.5;
	robot["Head"]->scale.z = 0.5;
	robot["Head"]->translation.y = +0.5 * robot["Body"]->scale.y + 0.5 * robot["Head"]->scale.y;
	robot["Head"]->SetParent(robot["Body"]);

	robot.emplace("LEye", new Cube(Vector4(1, 0, 0, 1)));
	robot["LEye"]->scale.x = 0.1;
	robot["LEye"]->scale.y = 0.05;
	robot["LEye"]->scale.z = 0.5;
	robot["LEye"]->translation.x = 0.1;
	robot["LEye"]->translation.y = 0.1;
	robot["LEye"]->translation.z = 0.05;
	robot["LEye"]->SetParent(robot["Head"]);

	robot.emplace("REye", new Cube(Vector4(1, 0, 0, 1)));
	robot["REye"]->scale.x = 0.1;
	robot["REye"]->scale.y = 0.05;
	robot["REye"]->scale.z = 0.5;
	robot["REye"]->translation.x = -0.1;
	robot["REye"]->translation.y = 0.1;
	robot["REye"]->translation.z = 0.05;
	robot["REye"]->SetParent(robot["Head"]);

}

void HomeworkBot::Render()
{
	for (auto& i : robot)
	{
		i.second->Render();
	}
}

void HomeworkBot::Update()
{
	KeyboardInput();
	Move();

	for (auto& i : robot)
	{
		i.second->Update();
	}
	
}

void HomeworkBot::KeyboardInput()
{
	if (!KEY_PRESS(VK_RBUTTON))
	{

		if (robot.count("Body")>0)
		{
		
			if (KEY_PRESS('A'))
			{
				state = MOVELSIDE;
				Vector3 dir = Vector3(robot["Body"]->GetRightVector().x, 0, robot["Body"]->GetRightVector().z).GetNormalized();

				robot["Body"]->translation += -dir * moveSpeed * DELTA_TIME;
				pressTime += DELTA_TIME *2;
			}
			if (KEY_PRESS('D'))
			{
				state = MOVERSIDE;
				Vector3 dir = Vector3(robot["Body"]->GetRightVector().x, 0, robot["Body"]->GetRightVector().z).GetNormalized();

				robot["Body"]->translation += dir * moveSpeed * DELTA_TIME;
				pressTime += DELTA_TIME * 2;
			}
			if (KEY_PRESS('S'))
			{

				state = MOVEBACKWARD;
				Vector3 dir = Vector3(robot["Body"]->GetForwardVector().x, 0, robot["Body"]->GetForwardVector().z).GetNormalized();
				robot["Body"]->translation += -dir * moveSpeed * DELTA_TIME;
				pressTime += DELTA_TIME * 2;
			}
			if (KEY_PRESS('W'))
			{
				state = MOVEFORWARD;
				Vector3 dir = Vector3(robot["Body"]->GetForwardVector().x, 0, robot["Body"]->GetForwardVector().z).GetNormalized();

				robot["Body"]->translation += dir * moveSpeed * DELTA_TIME;
				pressTime += DELTA_TIME * 2;
			}
			if (KEY_PRESS(VK_LBUTTON))
			{

				Vector3 delta = oldPos - mousePos;

				robot["Body"]->rotation.y += delta.x * DELTA_TIME * 5;
				robot["Head"]->rotation.y = 0;
				//robot["Body"]->rotation.x += delta.y * DELTA_TIME * 5;
			}
			else
			{
				Vector3 delta = oldPos - mousePos;

				robot["Head"]->rotation.y += delta.x * DELTA_TIME * 5;

			}
			if (KEY_UP('A')|| KEY_UP('S')|| KEY_UP('W')|| KEY_UP('D'))
			{
				state = IDLE;
				pressTime = 0;
			}

		}
	}
	oldPos = mousePos;

}

void HomeworkBot::Move()
{
	switch (state)
	{
	case IDLE:
		for (auto& i : robot)
		{
			if (i.first == "Head")
			{
				continue;
			}
			if (i.first == "Body")
			{
				i.second->rotation.z = 0;
				i.second->rotation.x = 0;
				continue;
			}
			i.second->rotation = Vector3(0, 0, 0);
		}
		break;
	case MOVEFORWARD:
		robot["Body"]->rotation.x = abs(0.1 * sin(pressTime));

		robot["LArm"]->rotation.x = 0.6 * sin(pressTime);
		robot["LFArm"]->rotation.x = min(0.6 * sin(pressTime), 0);
		robot["RFArm"]->rotation.x = min(0.6 * sin(-pressTime), 0);
		robot["RArm"]->rotation.x = 0.6 * sin(-pressTime);
		robot["LLeg"]->rotation.x = 0.6 * sin(-pressTime);
		robot["LFLeg"]->rotation.x = abs(0.6 * sin(pressTime));
		robot["RLeg"]->rotation.x = 0.6 * sin(pressTime);
		robot["RFLeg"]->rotation.x = abs(0.6 * sin(pressTime));
		break;
	case MOVELSIDE:
		robot["LLeg"]->rotation.z = abs(0.2 * sin(-pressTime));
		robot["Body"]->rotation.z = abs(0.2 * sin(-pressTime));
		//robot["LFLeg"]->rotation.z = abs(0.6 * sin(pressTime));
		robot["RLeg"]->rotation.z = -abs(0.5 * sin(pressTime));
		//robot["RFLeg"]->rotation.z = abs(0.6 * sin(pressTime));
		break;
	case MOVERSIDE:
		robot["LLeg"]->rotation.z = abs(0.5 * sin(-pressTime));
		robot["Body"]->rotation.z = -abs(0.2 * sin(-pressTime));

		//robot["LFLeg"]->rotation.z = abs(0.6 * sin(pressTime));
		robot["RLeg"]->rotation.z = -abs(0.2 * sin(pressTime));
		//robot["RFLeg"]->rotation.z = abs(0.6 * sin(pressTime));
		break;
	case MOVEBACKWARD:
		robot["LArm"]->rotation.x = 0.6 * sin(pressTime);
		robot["LFArm"]->rotation.x = min(0.6 * sin(pressTime), 0);
		robot["RFArm"]->rotation.x = min(0.6 * sin(-pressTime), 0);
		robot["RArm"]->rotation.x = 0.6 * sin(-pressTime);
		robot["LLeg"]->rotation.x = 0.6 * sin(-pressTime);
		robot["LFLeg"]->rotation.x = -min(0.6 * sin(pressTime), 0);
		robot["RLeg"]->rotation.x = 0.6 * sin(pressTime);
		robot["RFLeg"]->rotation.x = -min(0.6 * sin(-pressTime), 0);
		robot["Body"]->rotation.x = -abs(0.1 * sin(pressTime));
		break;
	default:
		break;
	}
}
