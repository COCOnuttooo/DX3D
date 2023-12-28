#pragma once
enum HomeworkBotState
{
	IDLE,
	MOVEFORWARD,
	MOVELSIDE,
	MOVERSIDE,
	MOVEBACKWARD
};

class HomeworkBot
{
public:
	HomeworkBot();
	~HomeworkBot();
	void Initialize();
	void Render();
	void Update();
	void KeyboardInput();
	void Motion();
	Transform* GetCameraLookAt() { return cameraLookAt; }
	void SetTerrain(Terrain* terrain) { this->ground = terrain; }
	
	void Debug();
private:
	float heightPivot = 1;
	float pressTime = 0;
	map<string, Cube*> robot;
	Vector3 oldPos;
	float moveSpeed = 5.0f;
	HomeworkBotState state = IDLE;
	Cube* xAxis;
	Cube* yAxis;
	Cube* zAxis;

	Transform* cameraLookAt;
	Terrain* ground;
};

