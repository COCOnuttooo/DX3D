#include "Framework.h"
#include "ModelClip.h"

ModelClip::ModelClip()
{
	Init();
}

ModelClip::~ModelClip()
{
	for (pair<string, KeyFrame*> pair : keyFrames)
		delete pair.second;

	keyFrames.clear();
}

void ModelClip::Init()
{
	eventsIterator = events.begin();
}

void ModelClip::Execute(float ratio)
{
	if (events.empty())
		return;

	if (eventsIterator == events.end())
		return;

	float temp = (*eventsIterator).first;

	if (temp > ratio) // pair.first
		return;

	//eventsIterator->second();

	function<void()> Function = eventsIterator->second;

	Function();

	eventsIterator++;

	//for (pair<float, function<void()>> pair : events)
	//{
	//	//delete pair.second;
	//}
}

void ModelClip::AddEvent(float ratio, function<void()> Event)
{
	events.emplace(ratio, Event);

	if (eventsIterator == events.end())
		Init();
}
