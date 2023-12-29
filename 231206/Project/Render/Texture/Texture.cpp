#include "Framework.h"
#include "Texture.h"
map<wstring, Texture*> Texture::textures;

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
	:srv(srv),image(move(image))
{
	
}

Texture::~Texture()
{
	srv->Release();
	image.Release();
}

Texture* Texture::Add(wstring file)
{
	if (!StartsWith(file,L"_Texture"))
		file = L"_Texture/" + file;

	assert(PathFileExists(file.c_str()));

	if (textures.count(file) >0)
		return textures[file];
	ScratchImage tempImage;

	wstring extension = Utility::GetExtension(file);
	if (extension == L"TGA" || extension == L"tga")
		LoadFromTGAFile(file.c_str() , nullptr, tempImage);
	else if (extension == L"DDS" || extension == L"dds")
		LoadFromDDSFile(file.c_str(),DDS_FLAGS_NONE, nullptr, tempImage);
	else
		LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, tempImage);

	ID3D11ShaderResourceView* tempSRV;
	CreateShaderResourceView
	(
		DEVICE, 
		tempImage.GetImages(), 
		tempImage.GetImageCount(), 
		tempImage.GetMetadata(), 
		&tempSRV
	);

	textures.emplace(file, new Texture(tempSRV, tempImage));




	return textures[file];
}

void Texture::Delete()
{
	for (auto& pair : textures)
	{
		delete pair.second;
	}
	textures.clear();
}

void Texture::PSSetShaderResources(UINT slot)
{
	DC->PSSetShaderResources(slot, 1, &srv);
}

vector<Vector4> Texture::ReadPixels()
{
	uint8_t* pixels = image.GetPixels();
	
	UINT size = image.GetPixelsSize() * 0.25f;

	float scale = 1.0f / 255.0f;

	vector<Vector4> colors;

	colors.resize(size);

	for (UINT i = 0; i < size; i++)
	{
		colors[i].x = pixels[i * 4 + 0] * scale;
		colors[i].y = pixels[i * 4 + 1] * scale;
		colors[i].z = pixels[i * 4 + 2] * scale;
		colors[i].w = pixels[i * 4 + 3] * scale;
	}

	return colors;
}
