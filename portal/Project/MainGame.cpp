#include "Framework.h"
#include "MainGame.h"
#include "Scene/TutorialScene.h"
#include "Scene/TextureScene.h"
#include "Scene/GridScene.h"
#include "Scene/TerrainScene.h"
#include "Scene/TerrainEditorScene.h"
#include "Scene/PortalScene.h"
MainGame::MainGame()
{
    char path[128];
    GetCurrentDirectoryA(128, path);
    projectDir = path;
	Initialize();
    SCENE->Create("Start", new PortalScene);
    //SCENE->Create("Start", new TextureScene);
    //SCENE->Create("Tutorial", new TutorialScene);
    SCENE->Add("Start");
    SCENE->Create("Grid", new GridScene);
    SCENE->Add("Grid");
    //SCENE->Add("Tutorial");
    Texture::Add(L"NoImage.jpg");
}

MainGame::~MainGame()
{
	Release();
    
}

void MainGame::Update()
{
    ENVIRONMENT->Update();
    KEYBOARD->Update();
    TIME->Update();
    SCENE->Update();

}

void MainGame::Render()
{
    ENVIRONMENT->Set();

    SCENE->Render();
}

void MainGame::PreRender()
{

    Device::GetInstance()->SetP1RTV();
    ENVIRONMENT->SetP1();
    SCENE->PreRender();

    Device::GetInstance()->SetP2RTV();
    ENVIRONMENT->SetP2();
    SCENE->PreRender();
    Device::GetInstance()->SetP1RTV();
    SCENE->P2ReRender();
    ENVIRONMENT->SetP1();
    Device::GetInstance()->SetP2RTV();
    SCENE->P1ReRender();
    ENVIRONMENT->SetP2();

    Device::GetInstance()->SetP1RTV();
    SCENE->P2ReRender();

    for (int i = 0; i < 10; i++)
    {


    }
    Device::GetInstance()->SetMainRTV();

}

void MainGame::PostRender()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    TIME->Render();
    static bool isWireFrame = false;
    static bool isGridScene = true;
    ImGui::Checkbox("WireFrame", &isWireFrame);
    if (isWireFrame)
        STATE->EnableWireFrame();
    else
        STATE->DisableWireFrame();

    if (ImGui::Checkbox("Greed Scene", &isGridScene))
    {
        if (isGridScene)
            SCENE->Add("Grid");
        else
            SCENE->Remove("Grid");

    }
    SCENE->PostRender();
    ENVIRONMENT->Debug();
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


}

void MainGame::Initialize()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);


    //scene = new TextureScene;
    Device::GetInstance();
    Environment::GetInstance();
    StateManager::GetInstance();
    //Create Vertex
}

void MainGame::Release()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

         Device::Delete();
    Environment::Delete();
         Shader::Delete();
           Time::Delete();
       Keyboard::Delete();
       StateManager::Delete();
       SceneManager::Delete();
       Texture::Delete();
         //delete scene;
}
