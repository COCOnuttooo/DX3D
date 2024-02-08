#pragma once
class CharacterScene : public Scene
{
public:
	CharacterScene();
	~CharacterScene();
	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;

	void SetClip();
private:
	Knight* player;

	

	

	

	

};
