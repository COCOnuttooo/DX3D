// header.h: 표준 시스템 포함 파일
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



#pragma comment	(lib,"d3d11.lib")
#pragma comment	(lib,"d3dcompiler.lib")
using namespace DirectX;
using namespace std;

#define WIN_HEIGHT	720.0f
#define WIN_WIDTH	1280.0f
#define DEVICE Device::GetInstance()->GetDevice()
#define DC     Device::GetInstance()->GetDC()


// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "Utility/Singleton.h"
#include "System/Device.h"


#include "MainGame.h"

extern HWND hWnd;