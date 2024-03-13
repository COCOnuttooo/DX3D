#pragma once

class ModelAnimatorInstancing : public ModelAnimator
{
protected:
	struct Frame
	{
		int    clipIndex = 0;
		UINT  frameIndex = 0;
		float       time = 0.0f;
		float      speed = 1.0f;
	};

	struct Motion
	{
		Motion()
		{
			nextFrame.clipIndex = -1;
		}

		float takeTime    = 0.2f;
		float tweenTime   = 0.0f;
		float runningTime = 0.0f;
		float padding;

		Frame curFrame, nextFrame;
	};

	struct Data
	{
		Motion motion[MAX_INSTANCE];
	};

	class FrameInstancingBuffer : public ConstBuffer<Data>
	{
	public:
		FrameInstancingBuffer() : ConstBuffer(data)
		{
		}

		Data data;
	};

public:
	ModelAnimatorInstancing(string name);
	~ModelAnimatorInstancing();

	void Update();
	void Render();

	void Debug();

	Transform* AddTransform();

	void PlayClip(UINT instanceIndex, int clipIndex, float speed = 1.0f, float takeTime = 0.1f);

private:
	void UpdateFrame(UINT instanceIndex);

private:
	vector<Transform*> transforms;

	vector<InstanceData> instanceDatas;

	VertexBuffer* instanceBuffer;

	UINT drawCount = 0;

	FrameInstancingBuffer* buffer;

	int instanceIndex = 0;
	int     clipIndex = 0;
};
