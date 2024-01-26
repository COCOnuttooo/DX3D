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
		Motion()
		{
			nextFrame.clipIndex = -1;
		}
		float takeTime = 0.2f;
		float tweenTime = 0.0f;
		float runningTime = 0.0f;
		float padding;

		Frame curFrame, nextFrame;
		
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
	void PlayClip(int clipIndex, float speed = 1.0f, float takeTime = 0.2f);

	Matrix GetTransformByBone(string boneName);

	ModelClip* Getclip(UINT index) { return clips[index]; }
private:
	void CreateTexture();
	void CreateClipTransform(UINT clipIndex);
	void UpdateFrame();
private:
	vector<ModelClip*> clips;

	FrameBuffer* buffer;
	ClipTransform* clipTransforms;
	ClipTransform* nodeTransforms;

	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* srv;


	bool isPlay = true;
};

