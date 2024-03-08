#pragma once
class SkyBox
{
public:
	SkyBox(wstring file);
	~SkyBox();

	void Render();
	void Update();

private:
	Texture* cubeMap;

	Sphere* sphere;
};

