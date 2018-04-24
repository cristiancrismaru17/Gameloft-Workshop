#pragma once
#include "TextureResource.h"
#include "../Utilities/utilities.h"

class Texture
{
public:

	int tWidth;
	int tHeight;
	int bpp;
	char *pixelArray;
	TextureResource* tr;
	GLuint textureId;
	Texture();
	~Texture();
	void Load(int id);
	void LoadSky(int id);
};