#pragma once
class BoxCube
{
public:
	BoxCube();
	~BoxCube();
	void Render();
	void Update();
	void Debug();
	void SetTexture(wstring file);
	void MouseInteraction();
	
private:
	Transform* mainBody;
	vector<Quad*> parts;
	vector<wstring> names;
	BoundingBox boxCubeBounds;
};

