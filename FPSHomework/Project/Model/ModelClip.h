#pragma once

class ModelClip
{
	friend class ModelAnimator;
public:
	ModelClip();
	~ModelClip();

	KeyFrame* GetKeyFrames(string boneName) { return keyFrames[boneName]; }

	void Init();
	void Execute(float ratio);

	void AddEvent(float ratio, function<void()> Event);

private:
	string name;

	UINT  frameCount = 0;

	float ticksPerSecond = 0.0f;
	float duration       = 0.0f;

	float playTime = 0.0f;

	unordered_map<string, KeyFrame*> keyFrames = {};


	multimap<float, function<void(void)>> events;

	multimap<float, function<void(void)>>::iterator eventsIterator;

	float ratio;
};
