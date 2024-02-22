#include "Framework.h"
#include "Onix.h"
Onix::Onix()
{
	for (int i = 0; i < 10; i++)
	{
		if (i !=0)
		{
			Vector3 dest = bodies[i - 1]->translation;
			dests.push_back(dest);
		}
		ColliderSphere* sphere = new ColliderSphere;
		sphere->translation.x = -i * 2;
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
}

void Onix::Update()
{
	Move();
	for (auto& i : bodies)
	{
		i->Update();
	}
}

void Onix::Render()
{
	for (auto& i : bodies)
	{
		i->Render();;
	}
}

void Onix::Move()
{
	deltaPos = bodies[0]->translation;
	bodies[0]->translation.x += 2 * DELTA_TIME;
	time += DELTA_TIME;

	bodies[0]->translation.z = 2 * sin(time);
	moveCool -= DELTA_TIME;

	if ((deltaPos - bodies[0]->translation).Length() != 0)
	{
		for (int i = 1; i < bodies.size(); i++)
			bodies[i]->translation = sources[i - 1] + (dests[i-1] - sources[i-1]) ;
	}
	if (moveCool <= 0 )
	{
		for (int i = 0; i < bodies.size()-1; i++)
		{
			if ((deltaPos - bodies[0]->translation).Length() == 0)
			{
				continue;
			}
			
			dests[i] = bodies[i]->translation;
			sources[i] = bodies[i + 1]->translation;
		}
		moveCool = 1;
	}

}

