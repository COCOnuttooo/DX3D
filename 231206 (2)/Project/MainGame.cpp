#include "Framework.h"
#include "MainGame.h"
#include "Scene/TutorialScene.h"
#include "Scene/TextureScene.h"
#include "Scene/GridScene.h"
MainGame::MainGame()
{
	Initialize();
    SCENE->Create("Start", new TextureScene);
    SCENE->Create("Tutorial", new TutorialScene);
    SCENE->Add("Start");
    SCENE->Create("Grid", new GridScene);
    SCENE->Add("Grid");
    SCENE->Add("Tutorial");
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
  //  ENVIRONMENT->Debug();
    /////////////////////////////////////
    SCENE->Render();
}

void MainGame::PreRender()
{
    SCENE->PreRender();
}

void MainGame::PostRender()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ENVIRONMENT->Debug();


    SCENE->PostRender();
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
         //delete scene;
}
