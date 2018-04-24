#include <stdio.h>
#include <map>
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "ModelResource.h"
#include "ShaderResource.h"
#include "TextureResource.h"

class ResourceManager
{
private:
	static ResourceManager* spInstance;
	//ResourceManager();
public:
	std::map<int, Model* > models;
	std::map<int, Shader* > shaders;
	std::map<int, Texture* > textures;

	std::map<int, ModelResource* > pModelResource;
	std::map<int, ShaderResource* > pShaderResource;
	std::map<int, TextureResource* > pTextureResource;

	
	static ResourceManager* getInstance();
	void freeResources();
	void Init(char* fileDir);

	Model* loadModel(int id);
	Shader* loadShader(int id);
	Texture* loadTexture(int id);
	
	~ResourceManager();
};
