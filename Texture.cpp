#include "stdafx.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "../Utilities/utilities.h"

void Texture::Load(int id)
{
	tr = ResourceManager::getInstance()->pTextureResource[id];

	if (tr->type.compare("cube"))
	{
		glGenTextures(1, &textureId);
		if (tr->type.compare("2d") == 0)
		{
			glBindTexture(GL_TEXTURE_2D, textureId);
		}
		else
		{
			throw "texture not 2d";
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tr->min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tr->mag_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tr->wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tr->wrap_t);

		pixelArray = LoadTGA((char *)tr->path.c_str(), &tWidth, &tHeight, &bpp);

		GLint texFormat = (bpp == 32 ? GL_RGBA : GL_RGB);

		glTexImage2D(GL_TEXTURE_2D, 0, texFormat, tWidth, tHeight, 0, texFormat, GL_UNSIGNED_BYTE, pixelArray);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		glGenTextures(1, &textureId);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, tr->min_filter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, tr->mag_filter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, tr->wrap_s);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, tr->wrap_t);

		glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

		pixelArray = LoadTGA((char *)tr->path.c_str(), &tWidth, &tHeight, &bpp);

		GLint texFormat = (bpp == 32 ? GL_RGBA : GL_RGB);

		int wb = tWidth * bpp / 8;
		int hb = tHeight * bpp / 8;

		char* buffer = new char[(bpp / 8 * tHeight * tWidth) + 1];


		int k = 0;
		for (int i = tHeight / 3; i < 2 * tHeight / 3; i++)
		{
			for (int j = wb / 2; j < 3 * wb / 4; j++)
			{
				buffer[k++] = pixelArray[i * wb + j];
				//printf("k = %d | res = %d | i = %d | j = %d\n", k-1, i * wb + j, i, j);
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, texFormat, tWidth / 4, tHeight / 3, 0, texFormat, GL_UNSIGNED_BYTE, buffer); //0

		k = 0;
		for (int i = tHeight / 3; i < 2 * tHeight / 3; i++)
		{
			for (int j = 0; j < wb / 4; j++)
			{
				buffer[k++] = pixelArray[i * wb + j];
				//printf("k = %d | res = %d | i = %d | j = %d\n", k-1, i * wb + j, i, j);
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, texFormat, tWidth / 4, tHeight / 3, 0, texFormat, GL_UNSIGNED_BYTE, buffer); //1

		k = 0;
		for (int i = 0; i < tHeight / 3; i++)
		{
			for (int j = wb / 4; j < wb / 2; j++)
			{
				buffer[k++] = pixelArray[i * wb + j];
				//printf("k = %d | res = %d | i = %d | j = %d\n", k-1, i * wb + j, i, j);
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, texFormat, tWidth / 4, tHeight / 3, 0, texFormat, GL_UNSIGNED_BYTE, buffer); //2

		k = 0;
		for (int i = 2 * tHeight / 3; i < tHeight; i++)
		{
			for (int j = wb / 4; j < wb / 2; j++)
			{
				buffer[k++] = pixelArray[i * wb + j];
				//printf("k = %d | res = %d | i = %d | j = %d\n", k-1, i * wb + j, i, j);
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, texFormat, tWidth / 4, tHeight / 3, 0, texFormat, GL_UNSIGNED_BYTE, buffer); //3

		k = 0;
		for (int i = tHeight / 3; i < 2 * tHeight / 3; i++)
		{
			for (int j = wb / 4; j < wb / 2; j++)
			{
				buffer[k++] = pixelArray[i * wb + j];
				//printf("k = %d | res = %d | i = %d | j = %d\n", k-1, i * wb + j, i, j);
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, texFormat, tWidth / 4, tHeight / 3, 0, texFormat, GL_UNSIGNED_BYTE, buffer); //4

		k = 0;
		for (int i = tHeight / 3; i < 2 * tHeight / 3; i++)
		{
			for (int j = 3 * wb / 4; j < wb; j++)
			{
				buffer[k++] = pixelArray[i * wb + j];
				//printf("k = %d | res = %d | i = %d | j = %d\n", k-1, i * wb + j, i, j);
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, texFormat, tWidth / 4, tHeight / 3, 0, texFormat, GL_UNSIGNED_BYTE, buffer); //5

		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}

Texture::Texture()
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
	/*delete &tWidth, &tHeight, &bpp, &pixelArray, &tr, &textureId;*/
}
