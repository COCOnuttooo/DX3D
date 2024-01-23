#include "Framework.h"
#include "ModelAnimator.h"
ModelAnimator::ModelAnimator(string name)
	:Model(name)
{
    buffer = new FrameBuffer;
    SetShader(L"09_ModelAnimator");
}

ModelAnimator::~ModelAnimator()
{
    for (auto& clip : clips)
        delete clip;
    delete buffer;
}

void ModelAnimator::Update()
{
    Model::Update();
}

void ModelAnimator::Render()
{
    if (texture == nullptr)
    {
        CreateTexture();
    }
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
    int& clipIndex = buffer->data.curFrame.clipIndex;

    ImGui::SliderInt("ClipIndex", &clipIndex, 0, clips.size() - 1);
    ImGui::SliderInt("Frame Index", (int*)&buffer->data.curFrame.frameIndex, 0, clips[clipIndex]->frameCount - 1);

    Model::Debug();
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
