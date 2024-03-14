#pragma once
class ParticleScene : public Scene
{
public:
	ParticleScene();
	~ParticleScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
private:
	bool isPlay = false;
	Model* rock;
	Onix* onix;
	Collider* target;
	MeteorEffect* meteorEffect;
	MeteorEffect* meteorEffect2;
	MeteorEffect* meteorEffect3;
	MeteorEffect* meteorEffect4;
	//
	Collider* collider;


};
