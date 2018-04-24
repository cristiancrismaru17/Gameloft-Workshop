#pragma once
#include <string>
#include <../../Utilities/utilities.h>

struct TextureResource
{
	int id;
	std::string type;
	std::string path;
	GLint min_filter;
	GLint mag_filter;
	GLint wrap_s;
	GLint wrap_t;
};