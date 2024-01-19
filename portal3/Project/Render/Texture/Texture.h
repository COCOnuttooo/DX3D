#pragma once
class Texture
{
public:
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	Texture(ID3D11ShaderResourceView* srv);
	~Texture();
	static Texture* Add(wstring file);
	static Texture* Add(wstring file, wstring key);
	static Texture* Add(ID3D11Texture2D** texture, wstring key);
	static void Delete();

	void PSSetShaderResources(UINT slot);
	vector<Vector4> ReadPixels();

	Vector2 GetSize() { return Vector2(image.GetMetadata().width, image.GetMetadata().height); }

	ID3D11ShaderResourceView* GetSRV() { return srv; }
private:
	static map<wstring, Texture*> textures;

	ScratchImage image;

	ID3D11ShaderResourceView* srv = nullptr;


};

