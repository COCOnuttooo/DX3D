#include "Framework.h"
#include "TutorialScene.h"
TutorialScene::TutorialScene()
{
    cube = new Cube;
    cube2 = new Cube(Vector4(0,1,0,1));
 /*   cube2->translation.z = 2.0f;*/
    cube2->translation.x = 1.0f;
    cube2->SetParent(cube);
    cube->SetPivot(Vector3(0.5f, 0.5f, 0.5f));
    cube2->SetPivot(Vector3(-0.5f, 0.5f, 0.5f));
}

TutorialScene::~TutorialScene()
{
    delete cube;
    delete cube2;
    
}

void TutorialScene::Update()
{
    cube->Update();
    cube2->Update();
    //cube->rotation.x += 0.0001f;
    //cube->rotation.y += 0.0003f;
    //cube->rotation.z += 0.0005f;

    //cube2->rotation.x += 0.0001f;
    //cube2->rotation.y += 0.0003f;
    //cube2->rotation.z += 0.0005f;
}

void TutorialScene::PreRender()
{
}

void TutorialScene::Render()
{
    cube->Render();
    cube2->Render();

}

void TutorialScene::PostRender()
{
    ImGui::Text("HelloWorld!");
}
