#pragma once
class ModelAnimator : public Model
{
protected:
	struct Frame
	{
		int clipIndex = 0;
		UINT frameIndex = 0;
		float time = 0.0f;
		float speed = 1.0f;

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

	void Update();
	void Render();

	void ReadClip(string file, UINT clipIndex = 0);

	void Debug();

	void CreateTexture();
private:
	void CreateClipTransform(UINT clipIndex);

private:
	vector<ModelClip*> clips;

	FrameBuffer* buffer;

	ClipTransform* clipTransforms;
	ClipTransform* nodeTransforms;

	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* srv;
};

