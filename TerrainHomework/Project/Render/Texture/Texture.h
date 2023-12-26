#pragma once
class Texture
{
public:
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();
	static Texture* Add(wstring file);
	static void Delete();

	void PSSetShaderResources(UINT slot);
	vector<Vector4> ReadPixels();

	Vector2 GetSize() { return Vector2(image.GetMetadata().width, image.GetMetadata().height); }
private:
	static map<wstring, Texture*> textures;

	ScratchImage image;

	ID3D11ShaderResourceView* srv;


};

