#include "stdafx.h"
#include "..\Utilities\rapidxml-1.13\rapidxml.hpp"
#include "..\Utilities\rapidxml-1.13\rapidxml_utils.hpp"
#include "..\Utilities\rapidxml-1.13\rapidxml_print.hpp"
#include "..\Utilities\rapidxml-1.13\rapidxml_iterators.hpp"
#include "ResourceManager.h"
#include <map>
#include "stogli.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "ModelResource.h"
#include "ShaderResource.h"
#include "TextureResource.h"

ResourceManager* ResourceManager::spInstance = NULL;

ResourceManager* ResourceManager::getInstance()
{
	if (!spInstance)
	{
		spInstance = new ResourceManager();
	}
	return spInstance;
}

void ResourceManager::Init(char *fileDir)
{
	rapidxml::file<> docFile(fileDir);
	rapidxml::xml_document<> doc;
	doc.parse<0>(docFile.data());

	rapidxml::xml_node<>* node;

	//model
	node = doc.first_node()->first_node("models")->first_node("model");
	for (rapidxml::xml_node<>* n = node; n; n = n->next_sibling())
	{
		int id = atoi(n->first_attribute("id")->value());

		pModelResource[id] = new ModelResource();

		//ID
		pModelResource[id]->id = id;

		//Path
		pModelResource[id]->path.assign(n->first_node("path")->value());
	}

	//Shader
	node = doc.first_node()->first_node("shaders")->first_node("shader");
	for (rapidxml::xml_node<>* n = node; n; n = n->next_sibling())
	{
		int id = atoi(n->first_attribute("id")->value());

		pShaderResource[id] = new ShaderResource();

		//ID
		pShaderResource[id]->id = id;

		//FsPath
		pShaderResource[id]->fs.assign(n->first_node("fs")->value());

		//VsPath
		pShaderResource[id]->vs.assign(n->first_node("vs")->value());
	}

	//Texture
	node = doc.first_node()->first_node("textures")->first_node("texture");
	for (rapidxml::xml_node<>* n = node; n; n = n->next_sibling())
	{
		int id = atoi(n->first_attribute("id")->value());

		pTextureResource[id] = new TextureResource();

		//ID
		pTextureResource[id]->id = id;

		//Type
		pTextureResource[id]->type.assign(n->first_attribute("type")->value());

		//Path
		pTextureResource[id]->path.assign(n->first_node("path")->value());

		////minFilter
		pTextureResource[id]->min_filter = stogli(n->first_node("min_filter")->value());

		////magFilter
		pTextureResource[id]->mag_filter = stogli(n->first_node("mag_filter")->value());

		////wrap_s
		pTextureResource[id]->wrap_s = stogli(n->first_node("wrap_s")->value());

		////wrap_t
		pTextureResource[id]->wrap_t = stogli(n->first_node("wrap_t")->value());
	}
}

Model* ResourceManager::loadModel(int id)
{
	std::map<int, Model*>::iterator it;

	it = models.find(id);

	if (it != models.end())
	{
		return models[id];
	}
	else
	{
		models[id] = new Model();
		if (id != 5)
		{
			models[id]->Load(id);
		}
		else
		{
			models[id]->LoadTerrain(id);
		}
		return models[id];
	}
}

Shader* ResourceManager::loadShader(int id)
{
	std::map<int, Shader*>::iterator it;

	it = shaders.find(id);

	if (it != shaders.end())
	{
		return shaders[id];
	}
	else
	{
		shaders[id] = new Shader();
		shaders[id]->Load(id);
		return shaders[id];
	}
}

Texture* ResourceManager::loadTexture(int id)
{
	std::map<int, Texture*>::iterator it;

	it = textures.find(id);

	if (it != textures.end())
	{
		return textures[id];
	}
	else
	{
		textures[id] = new Texture();
		textures[id]->Load(id);
		return textures[id];
	}
}

void ResourceManager::freeResources()
{
	delete &spInstance, pModelResource, pShaderResource, pTextureResource, models, shaders, textures;
}

ResourceManager::~ResourceManager()
{
	freeResources();
}