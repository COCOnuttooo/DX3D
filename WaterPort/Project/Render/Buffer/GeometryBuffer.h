#pragma once
class GeometryBuffer
{
	enum RenderTargets
	{
		DIFFUSE, NORMAL, SPECULAR, SIZE
	};
public:
	GeometryBuffer();
	~GeometryBuffer();

	void SetMultiRenderTarget();
	void PostRender();
	void SetSRVs();


private:
	class RenderTarget* rtvs[SIZE];

	class DepthStencil* depthStencil;

	class Quad* quads[SIZE + 1];

	class ID3D11ShaderResourceView* srvs[SIZE + 1];

};

