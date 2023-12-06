﻿// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "__Others/targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <functional>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace std;

#define WIN_WIDTH  1280.0f
#define WIN_HEIGHT  720.0f

#define DEVICE Device::GetInstance()->GetDevice()
#define DC     Device::GetInstance()->GetDC()
#define ENVIRONMENT Environment::GetInstance()


typedef XMMATRIX Matrix;


#include "Utility/Singleton.h"

#include "System/Device.h"
#include "Render/Buffer/VertexLayout.h"
#include "Render/Buffer/VertexBuffer.h"
#include "Render/Buffer/IndexBuffer.h"
#include "Render/Buffer/ConstBuffer.h"
#include "Render/Buffer/GlobalBuffer.h"


#include "Render/Shader/Shader.h"
#include "Render/Shader/VertexShader.h"
#include "Render/Shader/PixelShader.h"

#include "System/Camera.h"
#include "System/Environment.h"

#include "Render/Material.h"
#include "Render/Mesh.h"

#include "Object/GameObject.h"
#include "Object/Basic/Cube.h"

#include "MainGame.h"

extern HWND hWnd;