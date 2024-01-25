#include "Framework.h"
#include "ModelAnimator.h"
ModelAnimator::ModelAnimator(string name)
	:Model(name)
{
    buffer = new FrameBuffer;
    SetShader(L"09_ModelAnimator");
    if (texture == nullptr)
    {
        CreateTexture();
    }
    socketRH = new Transform;
    //socketRH->SetParent(this);
}

ModelAnimator::~ModelAnimator()
{
    for (auto& clip : clips)
        delete clip;
    delete buffer;
    texture->Release();
    srv->Release();
    delete socketRH;
}

void ModelAnimator::Update()
{

    Model::Update();
    UpdateFrame();
    UpdateSockets();
    //GetTransformByBone("mixamorig:RightHand");
}

void ModelAnimator::Render()
{
    if (texture == nullptr)
        CreateTexture();


    buffer->SetVSBuffer(3);
    DC->VSSetShaderResources(0, 1, &srv);
    Model::Render();
}

void ModelAnimator::ReadClip(string file, UINT clipIndex)
{
    string path = "_ModelData/Clip/" + name + "/" + file  +"_" + to_string(clipIndex) + ".clip";

    assert(PathFileExistsA(path.c_str()));
    BinaryReader data(path);

    ModelClip* clip = new ModelClip();
    clip->name = data.ReadString();
    clip->ticksPerSecond = data.ReadFloat();
    clip->frameCount = data.ReadUint();
    //clip->duration = data.ReadFloat();

    UINT keyFrameCount = data.ReadUint();

    for (UINT i = 0; i < keyFrameCount; i++)
    {
        KeyFrame* keyFrame = new KeyFrame;
        keyFrame->boneName = data.ReadString();

        UINT keyTransformCount = data.ReadUint();

        if (keyTransformCount > 0)
        {
            keyFrame->transforms.resize(keyTransformCount);

            void* ptr = (void*)keyFrame->transforms.data();
            data.ReadData(&ptr, sizeof(KeyTransform) * keyTransformCount);
        }

        clip->keyFrames.emplace(keyFrame->boneName, keyFrame);
    }

    clips.emplace_back(clip);
}

void ModelAnimator::Debug()
{
    static int clipIndex = 0;

    ImGui::Text("ModelAnimator Option");
    
    if (ImGui::SliderInt("ClipIndex", &clipIndex, 0, clips.size() - 1))
    {
        PlayClip(clipIndex, 1.f,2.f);
    }

    ImGui::SliderInt("Frame Index", (int*)&buffer->data.curFrame.frameIndex, 0, clips[clipIndex]->frameCount - 1);
    ImGui::SliderFloat("Clip Speed", &buffer->data.curFrame.speed, 0.1f, 10.0f);
    Model::Debug();
}

void ModelAnimator::PlayClip(int clipIndex, float speed, float takeTime)
{
    buffer->data.nextFrame.clipIndex = clipIndex;
    buffer->data.nextFrame.speed     = speed;
    buffer->data.takeTime            = takeTime;

}

Matrix ModelAnimator::GetTransformByBone(string boneName)
{
    if (texture == nullptr)
        return XMMatrixIdentity();
    UINT clipIndex = buffer->data.curFrame.clipIndex;
    UINT frameIndex = buffer->data.curFrame.frameIndex;

    for (NodeData node : nodes)
    {
        if (node.name == boneName)
        {
            socketRH->GetWorld() = nodeTransforms[clipIndex].transform[frameIndex][node.index] * this->world;
            return nodeTransforms[clipIndex].transform[frameIndex][node.index];
        }
    }

    return XMMatrixIdentity();
}

void ModelAnimator::CreateClipTransform(UINT clipIndex)
{
    ModelClip* clip = clips[clipIndex];

    for (UINT f = 0; f < clip->frameCount; f++)
    {
        UINT nodeIndex = 0;

        for (NodeData node : nodes)
        {
            Matrix animWorld;

            KeyFrame* frame = clip->GetKeyFrames(node.name);

            if (frame != nullptr)
            {
                KeyTransform transform = frame->transforms[f];

                Matrix S = XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z);
                Matrix R = XMMatrixRotationQuaternion(XMLoadFloat4(&transform.rotation));
                Matrix T = XMMatrixTranslation(transform.translation.x, transform.translation.y, transform.translation.z);

                animWorld = S * R * T;
            }
            else
            {
                animWorld = XMMatrixIdentity();
            }

            Matrix parentWorld;

            int parentIndex = node.parent;

            if (parentIndex < 0)
                parentWorld = XMMatrixIdentity();
            else
                parentWorld = nodeTransforms[clipIndex].transform[f][parentIndex];

            nodeTransforms[clipIndex].transform[f][nodeIndex] = animWorld * parentWorld;

            //vector<BoneData> bones = reader->bones;

            if (boneMap.count(node.name)>0)
            {
                UINT boneIndex = boneMap[node.name];

                Matrix transform = bones[boneIndex].offset;

                transform *= nodeTransforms[clipIndex].transform[f][nodeIndex];

                clipTransforms[clipIndex].transform[f][boneIndex] = transform;
            }

            nodeIndex++;
        }
    }
}

void ModelAnimator::UpdateFrame()
{
    Motion& motion = buffer->data;

    ModelClip* clip = clips[motion.curFrame.clipIndex];
    motion.curFrame.time += Time::Delta() * clip->ticksPerSecond * motion.curFrame.speed;

    if (motion.curFrame.time >= 1.0f)
    {
        motion.curFrame.frameIndex = (motion.curFrame.frameIndex + 1) % (clip->frameCount -1);
        motion.curFrame.time = 0.0f;
    }
    if (motion.nextFrame.clipIndex == -1)
        return;

    motion.tweenTime += DELTA_TIME / motion.takeTime;

    clip = clips[motion.nextFrame.clipIndex];
    if (motion.tweenTime >= 1.0f)
    {
        motion.curFrame  = motion.nextFrame;
        motion.tweenTime = 0.0f;
        motion.nextFrame.clipIndex = -1;
        motion.nextFrame.frameIndex = 0;
        motion.nextFrame.time = 0;
    }
    else
    {
        motion.nextFrame.time += DELTA_TIME * clip->ticksPerSecond * motion.nextFrame.speed;

        if (motion.nextFrame.time >= 1.0f)
        {
            motion.nextFrame.frameIndex = (motion.nextFrame.frameIndex + 1) % (clip->frameCount - 1);
            motion.nextFrame.time = 0.0f;
        }

    }
}

void ModelAnimator::CreateTexture()
{
    UINT clipCount = clips.size();

    clipTransforms = new ClipTransform[clipCount];
    nodeTransforms = new ClipTransform[clipCount];

    for (UINT i = 0; i < clipCount; i++)
    {
        CreateClipTransform(i);
    }

    D3D11_TEXTURE2D_DESC desc = {};

    desc.Width = MAX_BONE * 4;
    desc.Height = MAX_FRAME;
    desc.ArraySize = clipCount;
    desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    desc.Usage = D3D11_USAGE_IMMUTABLE;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.MipLevels = 1;
    desc.SampleDesc.Count = 1;

    UINT pageSize = MAX_BONE * sizeof(Matrix) * MAX_FRAME;

    void* ptr = VirtualAlloc(nullptr, pageSize * clipCount, MEM_RESERVE, PAGE_READWRITE);

    for (UINT c = 0; c < clipCount; c++)
    {
        UINT start = c * pageSize;

        for (UINT i = 0; i < MAX_FRAME; i++)
        {
            void* temp = (BYTE*)ptr + MAX_BONE * i * sizeof(Matrix) + start;

            VirtualAlloc(temp, MAX_BONE * sizeof(Matrix), MEM_COMMIT, PAGE_READWRITE);
            memcpy(temp, clipTransforms[c].transform[i], MAX_BONE * sizeof(Matrix));
        }
    }

    D3D11_SUBRESOURCE_DATA* subResource = new D3D11_SUBRESOURCE_DATA[clipCount];

    for (UINT c = 0; c < clipCount; c++)
    {
        void* temp = (BYTE*)ptr + c * pageSize;

        subResource[c].pSysMem = temp;
        subResource[c].SysMemPitch = MAX_BONE * sizeof(Matrix);
        subResource[c].SysMemSlicePitch = pageSize;
    }

    DEVICE->CreateTexture2D(&desc, subResource, &texture);

    delete[] subResource;
    VirtualFree(ptr, 0, MEM_RELEASE); // 0 ?

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

    srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
    srvDesc.Texture2DArray.MipLevels = 1;
    srvDesc.Texture2DArray.ArraySize = clipCount;

    DEVICE->CreateShaderResourceView(texture, &srvDesc, &srv);
}
