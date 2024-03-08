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

	Particle* particle;
	
	Collider* collider;


};
