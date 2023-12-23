#pragma once
class Texture
{
public:
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();
	static Texture* Add(wstring file);
	static void Delete();

	void PSSetShaderResources(UINT slot);

private:
	static map<wstring, Texture*> textures;

	ScratchImage image;

	ID3D11ShaderResourceView* srv;


};

