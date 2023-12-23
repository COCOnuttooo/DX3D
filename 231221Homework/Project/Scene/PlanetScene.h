#pragma once
class PlanetScene : public Scene
{
public:
	PlanetScene();
	~PlanetScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

	void CreateRandomOrbit(Planet* planet, float length);
private:
	vector<Planet*> planets;

};

