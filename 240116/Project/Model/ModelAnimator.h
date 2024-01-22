#pragma once
class ModelAnimator : public Model
{
protected:
	struct Frame
	{
		int clipIndex = 0;
		UINT curFrame = 0;
		float time = 0.0f;
		float speed = 0.0f;

	};
	struct Motion
	{
		float takeTime = 0.2f;
		float tweenTime = 0.0f;
		float runningTime = 0.0f;
		float padding;

		Frame curFrame;
	};

	class FrameBuffer : public ConstBuffer<Motion>
	{
	public:
		FrameBuffer() : ConstBuffer(data )
		{

		}
		Motion data;
	};

public:
	ModelAnimator(string name);
	~ModelAnimator();

private:
	vector<ModelClip> clips;
};

