#pragma once
class ModelClip
{
	friend class ModelAnimator;
public:
	ModelClip();
	~ModelClip();

	KeyFrame* GetKeyFrames(string boneName) { return keyFrames[boneName]; }
private:
	string name;

	UINT frameCount = 0;

	float ticksPerSecond = 0.0f;
	float duration = 0.0f;

	float playTime = 0.0f;

	unordered_map<string, KeyFrame*> keyFrames = {};

};

