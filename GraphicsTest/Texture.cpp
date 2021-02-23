#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture(std::string fileName)
{
	ImageRenderer* r = ImageRenderer::GetInstance();
	int w;
	int h;
	int channels;
	unsigned char* data = stbi_load(fileName.c_str(), &w, &h, &channels, 0);
	textureId = r->UploadTexture(data, w, h, channels);
	stbi_image_free(data);
}

void Texture::Bind(int textureUnit)
{
	ImageRenderer* r = ImageRenderer::GetInstance();
	r->BindTexture(textureId);
	r->ActiveTexture(textureUnit);
}

void Texture::Unbind()
{
	ImageRenderer* r = ImageRenderer::GetInstance();
	r->UnbindTexture();
}
