#pragma once
struct Ray
{
	Vector3 origin;    //������
	Vector3 direction; //����
};

struct HitResult
{
	Vector3 imapactPoint;
	float distance;
};
class Collider : public GameObject<Vertex>
{



public:
	Collider();
	virtual ~Collider();
	void Render();

	virtual bool Collision(const IN Ray& ray,OUT HitResult* result) = 0;
	virtual bool Collision(class ColliderBox* other)     = 0;
	virtual bool Collision(class ColliderSphere* other)  = 0;
	virtual bool Collision(class ColliderCapsule* other) = 0;

	void SetColor(float r, float g, float b) { material->GetBuffer()->data.diffuse = { r,g,b,1.0f }; }


private:
	




};

