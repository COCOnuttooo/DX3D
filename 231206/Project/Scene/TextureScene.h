#pragma once
class TextureScene : public Scene
{
public:
	TextureScene();
	~TextureScene();
	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;

private:
	Quad* quad;
	
	// Scene을(를) 통해 상속됨

};


