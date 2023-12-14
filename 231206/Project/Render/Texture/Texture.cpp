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
	file = L"_Texture/" + file;
	assert(PathFileExists(file.c_str()));

	if (textures.count(file) >0)
		return textures[file];
	ScratchImage tempImage;
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

void Texture::PSSetShaderResources(UINT slot)
{
	DC->PSSetShaderResources(slot, 1, &srv);
}
