#pragma once
#include "../../Utilities/utilities.h"

GLint stogli(char* s)
{
	if (!stricmp(s, "GL_NEAREST_MIPMAP_NEAREST"))
		return GL_NEAREST_MIPMAP_NEAREST;
	else if (!stricmp(s, "GL_LINEAR_MIPMAP_NEAREST"))
		return GL_LINEAR_MIPMAP_NEAREST;
	else if (!stricmp(s, "GL_NEAREST_MIPMAP_LINEAR"))
		return GL_NEAREST_MIPMAP_LINEAR;
	else if (!stricmp(s, "GL_LINEAR_MIPMAP_LINEAR"))
		return GL_LINEAR_MIPMAP_LINEAR;
	else if (!stricmp(s, "GL_NEAREST"))
		return GL_NEAREST;
	else if (!stricmp(s, "GL_LINEAR"))
		return GL_LINEAR;
	else if (!stricmp(s, "GL_REPEAT"))
		return GL_REPEAT;
	else if (!stricmp(s, "GL_CLAMP_TO_EDGE"))
		return GL_CLAMP_TO_EDGE;
	else if (!stricmp(s, "GL_MIRRORED_REPEAT"))
		return GL_MIRRORED_REPEAT;
	return -1;
}