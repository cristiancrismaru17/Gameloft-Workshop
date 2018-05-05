#include "stdafx.h"
#include "..\Utilities\rapidxml-1.13\rapidxml.hpp"
#include "..\Utilities\rapidxml-1.13\rapidxml_utils.hpp"
#include "..\Utilities\rapidxml-1.13\rapidxml_print.hpp"
#include "..\Utilities\rapidxml-1.13\rapidxml_iterators.hpp"
#include <stdio.h>
#include <string>
#include <map>
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Light.h"
#include "Fire.h"
#include "AmbientLight.h"
#include "../Utilities/utilities.h"

SceneManager* SceneManager::spInstance = NULL;

SceneManager* SceneManager::getInstance()
{
	if (!spInstance)
	{
		spInstance = new SceneManager();
	}
	return spInstance;
}

void SceneManager::Init(char* fileDir, ESContext *esContext)
{
	rapidxml::file<> docFile(fileDir);
	rapidxml::xml_document<> doc;
	doc.parse<0>(docFile.data());

	//background
	rapidxml::xml_node<>* node = doc.first_node()->first_node("backgroundColor");
	if (node != NULL)
	{
		glClearColor((float)atof(node->first_node("r")->value()),
			(float)atof(node->first_node("g")->value()),
			(float)atof(node->first_node("b")->value()),
			1.0f);
	}

	//Camera
	node = doc.first_node()->first_node("cameras")->first_node("camera");
	if (node != NULL)
	{
		for (rapidxml::xml_node<>* n = node; n; n = n->next_sibling())
		{
			int camId = atoi(n->first_attribute("id")->value());
			Vector3 cam_pos = (Vector3((float)atof(node->first_node("position")->first_node("x")->value()), (float)atof(node->first_node("position")->first_node("y")->value()), (float)atof(node->first_node("position")->first_node("z")->value())));
			Vector3 cam_target = (Vector3((float)atof(node->first_node("target")->first_node("x")->value()), (float)atof(node->first_node("target")->first_node("y")->value()), (float)atof(node->first_node("target")->first_node("z")->value())));
			Vector3 cam_up = (Vector3((float)atof(node->first_node("up")->first_node("x")->value()), (float)atof(node->first_node("up")->first_node("y")->value()), (float)atof(node->first_node("up")->first_node("z")->value())));
			float transSpeed = ((float)atof(node->first_node("translationSpeed")->value()));
			float rotSpeed = ((float)atof(node->first_node("rotationSpeed")->value()));
			float cam_fov = ((float)atof(node->first_node("fov")->value()));
			float cam_near = ((float)atof(node->first_node("near")->value()));
			float cam_far = ((float)atof(node->first_node("far")->value()));

			cameras[camId] = new Camera(cam_pos, cam_target, cam_up, transSpeed, rotSpeed, cam_near, cam_far, cam_fov);
			cameras[camId]->updateWorldView();
		}
	}

	//objects
	node = doc.first_node()->first_node("objects")->first_node("object");
	for (rapidxml::xml_node<>* n = node; n; n = n->next_sibling())
	{
		//ObjectID
		int id = atoi(n->first_attribute("id")->value());
		
		std::string objType;  objType.assign(n->first_node("type")->value());

		if (objType.compare("skybox") == 0)
		{
			Skybox *so = new Skybox();
			so->type.assign(objType);
			so->offsetY = (float)atof(n->first_node("offsetY")->value());
			sceneObjects[id] = (SceneObject *)so;
		}
		else if (objType.compare("terrain") == 0)
		{
			Terrain *to = new Terrain();
			to->type.assign(objType);
			to->offsetY = (float)atof(n->first_node("offsetY")->value());
			to->cellSize = (float)atof(n->first_node("cellSize")->value());
			to->verticalCells = (int)(float)atof(n->first_node("verticalCells")->value());
			to->horizontalCells = (int)(float)atof(n->first_node("horizontalCells")->value());
			sceneObjects[id] = (SceneObject *)to;
		}
		else if (objType.compare("fire") == 0)
		{
			Fire *fo = new Fire();
			fo->type.assign(objType);
			fo->maxDisp = (float)atof(n->first_node("maxDisp")->value());
			fo->position = Vector3((float)atof(n->first_node("position")->first_node("x")->value()),
				(float)atof(n->first_node("position")->first_node("y")->value()),
				(float)atof(n->first_node("position")->first_node("z")->value()));
			fireObjects[id] = fo;
			sceneObjects[id] = (SceneObject *)fo;
		}
		else
		{
			sceneObjects[id] = new SceneObject();

			sceneObjects[id]->type.assign(objType);

			//Position
			sceneObjects[id]->position = Vector3((float)atof(n->first_node("position")->first_node("x")->value()),
												(float)atof(n->first_node("position")->first_node("y")->value()),
												(float)atof(n->first_node("position")->first_node("z")->value()));

			if (n->first_node("color"))
			{
				sceneObjects[id]->color = Vector3((float)atof(n->first_node("color")->first_node("r")->value()),
												(float)atof(n->first_node("color")->first_node("g")->value()),
												(float)atof(n->first_node("color")->first_node("b")->value()));
				sceneObjects[id]->color;
			}
			////followingCamera
			//if (n->first_node("followingCamera"))
			//{
			//	sceneObjects[id]->followingCamera = cameras[atoi(n->first_node("followingCamera")->first_node("cameras")->first_node("camera")->value())];
			//}
		}

		//Lights
		node = doc.first_node()->first_node("lights")->first_node("light");
		for (rapidxml::xml_node<>* n = node; n; n = n->next_sibling())
		{
			//LightID
			int id = atoi(n->first_attribute("id")->value());

			std::string lightType;  lightType.assign(n->first_node("type")->value());

			if (lightType.compare("ambiental") == 0)
			{
				ambientLight = new AmbientLight();

				ambientLight->color = Vector3((float)atof(n->first_node("color")->first_node("r")->value()),
					(float)atof(n->first_node("color")->first_node("g")->value()),
					(float)atof(n->first_node("color")->first_node("b")->value()));

				ambientLight->brightness = (float)atof(n->first_node("brightness")->value());
			}
			else
			{
				Light *light = new Light();

				light->type.assign(lightType);

				light->diffColor = Vector3((float)atof(n->first_node("diffuseColor")->first_node("r")->value()),
					(float)atof(n->first_node("diffuseColor")->first_node("g")->value()),
					(float)atof(n->first_node("diffuseColor")->first_node("b")->value()));

				light->specColor = Vector3((float)atof(n->first_node("specularColor")->first_node("r")->value()),
					(float)atof(n->first_node("specularColor")->first_node("g")->value()),
					(float)atof(n->first_node("specularColor")->first_node("b")->value()));

				if (n->first_node("associatedObject"))
				{
					light->followingObj = atoi(n->first_node("associatedObject")->value());
				}

				lights[id] = light;

				if (lightType.compare("point") == 0)
				{
					if (n->first_node("pos"))
					{
						light->pos = Vector3((float)atof(n->first_node("pos")->first_node("x")->value()),
											(float)atof(n->first_node("pos")->first_node("y")->value()),
											(float)atof(n->first_node("pos")->first_node("z")->value()));
					}

					if (n->first_node("pointID"))
					{
						light->pointID = (int)atof(n->first_node("pointID")->value());
					}
				}
				else if (lightType.compare("directional") == 0)
				{
					if (n->first_node("direction"))
					{
						light->dir = Vector3((float)atof(n->first_node("direction")->first_node("x")->value()),
							(float)atof(n->first_node("direction")->first_node("y")->value()),
							(float)atof(n->first_node("direction")->first_node("z")->value()));
					}
				}
				else if (lightType.compare("spotlight") == 0)
				{
					if (n->first_node("pos"))
					{
						light->pos = Vector3((float)atof(n->first_node("pos")->first_node("x")->value()),
							(float)atof(n->first_node("pos")->first_node("y")->value()),
							(float)atof(n->first_node("pos")->first_node("z")->value()));
					}
					if (n->first_node("direction"))
					{
						light->dir = Vector3((float)atof(n->first_node("direction")->first_node("x")->value()),
							(float)atof(n->first_node("direction")->first_node("y")->value()),
							(float)atof(n->first_node("direction")->first_node("z")->value()));
					}
				}
			}
		}
		
		//activeCamera
		activeCamera = cameras[atoi(doc.first_node()->first_node("activeCamera")->value())];

		//id
		sceneObjects[id]->id = id;

		//depthTest
		sceneObjects[id]->depthTest = atoi(n->first_node("depthTest")->value());

		//wired
		if (n->first_node("wired"))
		{
			sceneObjects[id]->wired = (_stricmp(n->first_node("wired")->value(), "true") == 0 ? true : false);
		}

		//name
		if (n->first_node("name"))
		{
			sceneObjects[id]->name = n->first_node("name")->value();
		}

		if(n->first_node("rotation"))
		{
			//Rotation
			sceneObjects[id]->rotation = Vector3((float)atof(n->first_node("rotation")->first_node("x")->value()),
				(float)atof(n->first_node("rotation")->first_node("y")->value()),
				(float)atof(n->first_node("rotation")->first_node("z")->value()));
		}

		//Scale
		sceneObjects[id]->scale = Vector3((float)atof(n->first_node("scale")->first_node("x")->value()),
			(float)atof(n->first_node("scale")->first_node("y")->value()),
			(float)atof(n->first_node("scale")->first_node("z")->value()));

		//depthTest
		if (n->first_node("depthTest"))
		{
			sceneObjects[id]->depthTest = (_stricmp(n->first_node("depthTest")->value(), "true") == 0 ? true : false);
		}

		//blend
		if (n->first_node("blend"))
		{
			sceneObjects[id]->blend = (_stricmp(n->first_node("blend")->value(), "true") == 0 ? true : false);
		}

		//Model
		if (_stricmp(n->first_node("model")->value(), "generated") != 0)
		{
			int modelId = atoi(n->first_node("model")->value());
			sceneObjects[id]->model = ResourceManager::getInstance()->loadModel(modelId);
		}
		else
		{
			int genId = 5;
			sceneObjects[id]->model = ResourceManager::getInstance()->loadModel(genId);
		}

		//Shader
		int shaderId = atoi(n->first_node("shader")->value());
		sceneObjects[id]->shader = ResourceManager::getInstance()->loadShader(shaderId);

		//Texture
		for (rapidxml::xml_node<>* it = n->first_node("textures")->first_node("texture"); it; it = it->next_sibling())
		{
			int texId = atoi(it->first_attribute("id")->value());
			sceneObjects[id]->textures[texId] = ResourceManager::getInstance()->loadTexture(texId);
		}

		if (objType.compare("terrain") == 0)
		{  
			Terrain *to;
			to = (Terrain *)sceneObjects[id];

			to->Init();
		}
		if (objType.compare("fire") == 0)
		{
			Fire *fo;
			fo = (Fire *)sceneObjects[id];

			fo->Init();
		}
	}
	
}

void SceneManager::Draw(ESContext *esContext)
{
	for (std::map<int, SceneObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
	{
		i->second->Draw();
	}
}

void SceneManager::Update(ESContext *esContext, float deltaTime)
{
	activeCamera->setDeltaTime(deltaTime);

	ScreenToClient(esContext->hWnd, &current_p);
	if (GetKeyState(VK_LBUTTON) & 0x100)
	{
		activeCamera->rotateOX((float)(Globals::screenHeight / 2.0f - 11 - current_p.y));
		activeCamera->rotateSceneOY(-1 * (float)(Globals::screenWidth / 2.0f - 8 - current_p.x));
	}
	GetCursorPos(&current_p);
	SetCursorPos((int)(Globals::screenWidth / 2.0f), (int)(Globals::screenHeight / 2.0f + 20));

	/*GetCursorPos(&current_p);
	if (GetKeyState(VK_LBUTTON) & 0x100)
	{
		GetCursorPos(&saved_p);
	}*/

	for (std::map<int, SceneObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
	{
		i->second->Update();
	}

	/*if (frameTotal < frameLimit)
	{
		frameTotal += 0.05f;
	}
	else
	{
		SceneManager::getInstance()->activeCamera->setDeltaTime(deltaTime);

		if (GetKeyState(VK_LBUTTON) & 0x100) {

			ScreenToClient(esContext->hWnd, &current_p);
			GetCursorPos(&current_p);

			if (current_p.x < Globals::screenWidth / 2) {
				if (activeCamera->clockWise[0] == false)
					activeCamera->clockWise[0] = true;
				activeCamera->unghiSpeed[0] -= 0.005f;
			}
			else {
				if (activeCamera->clockWise[0] == true)
					activeCamera->clockWise[0] = false;
				activeCamera->unghiSpeed[0] += 0.005f;
			}
			if (current_p.y < Globals::screenHeight / 2) {
				if (activeCamera->clockWise[1] == false)
					activeCamera->clockWise[1] = true;
				activeCamera->unghiSpeed[1] -= 0.005f;
			}
			else {
				if (activeCamera->clockWise[1] == true)
					activeCamera->clockWise[1] = false;
				activeCamera->unghiSpeed[1] += 0.005f;
			}
		}
		else
		{
			GetCursorPos(&current_p);
			GetCursorPos(&saved_p);
		}
		frameTotal = 0;
	}*/

}

SceneManager::~SceneManager()
{
	SceneManager::getInstance()->freeResources();
}

void SceneManager::freeResources()
{
	for (std::map<int, SceneObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
	{
		i->second->~SceneObject();
	}
}