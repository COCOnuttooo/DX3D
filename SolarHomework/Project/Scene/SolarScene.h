#pragma once
class SolarScene : public Scene
{
public:
	SolarScene();
	~SolarScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;
	void CreateRandomOrbit(Planet* planet, float length);
	void CreateOrbit(Planet* planet, float length, Vector3 orbitVec);

	void Initialize();

	void Debug();

	void MouseEvent();

private:
	bool isClicked = false;
	Transform* planetTest;
	XMFLOAT2 mouseNDCtest;
	float testB;
	float testC;
	vector<Planet*> planets;
	ReverseSphere* background;
	Disc* disc;
	//SolarBackground* background;
	float speed = 1;
	Vector3 sunPos = {0,0,0};

};

