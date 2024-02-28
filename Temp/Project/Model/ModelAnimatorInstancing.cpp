#include "Framework.h"
#include "ModelAnimatorInstancing.h"

ModelAnimatorInstancing::ModelAnimatorInstancing(string name)
	:ModelAnimator(name)
{
	instanceDatas.resize(MAX_INSTANCE);
	instanceBuffer = new VertexBuffer(instanceDatas);

	SetShader(L"14_ModelAnimatorInstancing");

	buffer = new FrameInstancingBuffer();
}

ModelAnimatorInstancing::~ModelAnimatorInstancing()
{
	
	delete buffer;
	delete instanceBuffer;
	for (Transform* transform : transforms)
	{
		delete transform;
	}
	transforms.clear();
}

void ModelAnimatorInstancing::Update()
{
	drawCount = 0;

	for (UINT i = 0; i < transforms.size(); i++)
	{
		if (!transforms[i]->GetIsActive())
			continue;

		transforms[i]->Update();

		instanceDatas[drawCount].world = XMMatrixTranspose(transforms[i]->GetWorld());
		instanceDatas[drawCount].index = i;

		drawCount++;
		UpdateFrame(i);
	}
	instanceBuffer->UpdateVertex(instanceDatas.data(), drawCount);
}

void ModelAnimatorInstancing::Render()
{
	if (texture == nullptr)
		CreateTexture();

	DC->VSSetShaderResources(0, 1, &srv);

	instanceBuffer->IASetBuffer(1);

	buffer->SetVSBuffer(3);

	__super::RenderInstanced(drawCount);
}

void ModelAnimatorInstancing::Debug()
{
	ImGui::Text("DrawCount : %d", drawCount);

	if (ImGui::Button("Add Model"))
		AddTransform();
	ImGui::SliderInt("InstanceIndex", &instanceIndex, 0, 127);
	ImGui::SliderInt("ClipIndex", &clipIndex, 0, clips.size() - 1);
	if (ImGui::Button("Play"))
	{
		PlayClip(instanceIndex, clipIndex);
	}


	for (Transform* transform : transforms)
		transform->Debug();
}

Transform* ModelAnimatorInstancing::AddTransform()
{
	Transform* transform = new Transform();

	transform->SetName(name + "_" + to_string(transforms.size()));
	transforms.emplace_back(transform);

	return transform;
}

void ModelAnimatorInstancing::PlayClip(UINT instanceIndex, int clipIndex, float speed, float takeTime)
{
	Motion& motion = buffer->data.motion[instanceIndex];
	clips[motion.curFrame.clipIndex]->Init();
	clips[clipIndex]->Init();

	motion.nextFrame.clipIndex = clipIndex;
	motion.nextFrame.speed = speed;
	motion.takeTime = takeTime;

	isPlay = true;
}

void ModelAnimatorInstancing::UpdateFrame(UINT instanceIndex)
{
	Motion& motion = buffer->data.motion[instanceIndex];

	ModelClip* clip = clips[motion.curFrame.clipIndex];

	motion.curFrame.time += Time::Delta() * clip->ticksPerSecond * motion.curFrame.speed;

	if (motion.curFrame.time >= 1.0f)
	{
		if (motion.curFrame.frameIndex == 0)
			clip->Init();

		float animRatio = (float)motion.curFrame.frameIndex / clip->frameCount;

		clip->Execute(animRatio);

		motion.curFrame.frameIndex = (motion.curFrame.frameIndex + 1) % (clip->frameCount - 1);
		motion.curFrame.time = 0.0f;
	}

	if (motion.nextFrame.clipIndex == -1)
		return;

	motion.tweenTime += Time::Delta() / motion.takeTime;

	clip = clips[motion.nextFrame.clipIndex];

	if (motion.tweenTime >= 1.0f)
	{
		motion.curFrame = motion.nextFrame;
		motion.tweenTime = 0.0f;

		motion.nextFrame.clipIndex = -1;
		motion.nextFrame.frameIndex = 0;
		motion.nextFrame.time = 0.0f;
	}
	else
	{
		motion.nextFrame.time += Time::Delta() * clip->ticksPerSecond * motion.nextFrame.speed;

		if (motion.nextFrame.time >= 1.0f)
		{
			motion.nextFrame.frameIndex = (motion.nextFrame.frameIndex + 1) % (clip->frameCount - 1);
			motion.nextFrame.time = 0.0f;
		}
	}
}
