#pragma once
class MeteorEffect
{
public:
	MeteorEffect(Transform* target);
	~MeteorEffect();
	void Update();
	void Render();
	void Play();
	void Stop();
private:
	bool isActive = false;
	Particle* particle;
	Particle* particle2;
	Particle* particle3;
	Particle* particle4;
};

