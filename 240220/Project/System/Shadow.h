#pragma once
class Shadow
{
public:
	Shadow(UINT width = 2048, UINT height = 2048);
	~Shadow();

	void SetPreRender();
	void SetRender();

	void PostRender();
private:

	void SetViewProjection();



private:
	UINT width, height;

	RenderTarget* renderTarget;
	DepthStencil* depthStencil;

	ViewBuffer*   viewBuffer;
	MatrixBuffer* projBuffer;

	Quad* quad;

};

