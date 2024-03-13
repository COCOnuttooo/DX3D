#pragma once

class Texture
{
public:
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();

	static Texture* Add(wstring file);
	static Texture* Add(wstring file, wstring key);
	static Texture* Add(wstring key, ID3D11ShaderResourceView* srv);
	static void Delete();

	void PSSetShaderResources(UINT slot);
	void DSSetShaderResources(UINT slot);

	vector<Vector4> ReadPixels();

	Vector2 GetSize() { return Vector2(image.GetMetadata().width, image.GetMetadata().height); }

	ID3D11ShaderResourceView* GetSRV() { return srv; }

	wstring GetPath() { return path; }

private:
	static map<wstring, Texture*> textures;

	ScratchImage image;

	ID3D11ShaderResourceView* srv = nullptr;

	wstring path;
};
