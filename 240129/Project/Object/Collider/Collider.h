#pragma once
class Collider : public GameObject<Vertex>
{
protected:
	enum Type
	{
		BOX, SPHERE, CAPSULE
	};
public:
	Collider();
	virtual ~Collider();
	void Render();
private:
	

private:



};

