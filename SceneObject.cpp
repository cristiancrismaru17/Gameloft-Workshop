#include "stdafx.h"
#include <stdio.h>
#include <map>
#include "SceneObject.h"
#include "SceneManager.h"
#include "Terrain.h"
#include "Skybox.h"
#include "Fire.h"
#include "AmbientLight.h"
#include "Light.h"
#include "../Utilities/utilities.h"

SceneObject::SceneObject()
{
	aux.SetIdentity();
	T.SetIdentity();
	R.SetIdentity();
	pitch.SetIdentity();
	yaw.SetIdentity();
}

void SceneObject::SendCommonData()
{
	SceneManager *sm = SceneManager::getInstance();

	//texturi
	int i = 0;
	if (type.compare("skybox") == 0)
	{
		for (std::map<int, Texture *>::iterator it = textures.begin(); it != textures.end(); it++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_CUBE_MAP, it->second->textureId);

			if (shader->textureUniform[i] != -1)
			{
				glUniform1i(shader->textureUniform[i], i);
			}
			i++;
		}
	}
	else if (type.compare("terrain") == 0)
	{
		for (std::map<int, Texture *>::iterator it = textures.begin(); it != textures.end(); it++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, it->second->textureId);

			if (shader->textureUniform[i] != -1)
			{
				glUniform1i(shader->textureUniform[i], i);
			}
			i++;
		}
	}
	else if (type.compare("fire") == 0)
	{
		for (std::map<int, Texture *>::iterator it = textures.begin(); it != textures.end(); it++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, it->second->textureId);

			if (shader->textureUniform[i] != -1)
			{
				glUniform1i(shader->textureUniform[i], i);
			}
			i++;
		}

	}
	else
	{
		for (std::map<int, Texture *>::iterator it = textures.begin(); it != textures.end(); it++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, it->second->textureId);
			if (shader->textureUniform[i] != -1)
			{
				glUniform1i(shader->textureUniform[i], i);
			}
		}
	}

	//pos
	if (shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	//normals
	if (shader->normals != -1)
	{
		glEnableVertexAttribArray(shader->normals);
		glVertexAttribPointer(shader->normals, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(2 * sizeof(Vector3)));
	}

	//uv
	if (shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvAttribute);
		glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(5 * sizeof(Vector3)));
	}


	//color
	if (shader->colorAttribute != -1)
	{
		glEnableVertexAttribArray(shader->colorAttribute);
		glVertexAttribPointer(shader->colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)sizeof(Vector3));
	}

	if (shader->solidColor != -1)
	{
		glEnableVertexAttribArray(shader->solidColor);
		glUniform3f(shader->solidColor, color[0], color[1], color[2]);
	}

	//MVP
	if (shader->transformationMatrix != -1)
	{
		glUniformMatrix4fv(shader->transformationMatrix, 1, GL_FALSE, (GLfloat *)M.m);
	}
	if (shader->projectionMatrix != -1)
	{
		glUniformMatrix4fv(shader->projectionMatrix, 1, GL_FALSE, (GLfloat *)P.m);
	}
	if (shader->viewMatrix != -1)
	{
		glUniformMatrix4fv(shader->viewMatrix, 1, GL_FALSE, (GLfloat *)V.m);
	}

	//skyColor
	if (shader->skyColor != -1)
	{
		GLfloat skyColour[3] = { 0.235f, 0.267f, 0.333f };
		glEnableVertexAttribArray(shader->skyColor);
		glUniform3f(shader->skyColor, skyColour[0], skyColour[1], skyColour[2]);
	}

	//cameraPosition
	if (shader->cameraPos != -1)
	{
		glEnableVertexAttribArray(shader->cameraPos);
		glUniform3f(shader->cameraPos, sm->activeCamera->getPosition()[0], sm->activeCamera->getPosition()[1], sm->activeCamera->getPosition()[2]);
	}

	//Material properties
	if (shader->materialAmbient != -1)
	{
		glEnableVertexAttribArray(shader->materialAmbient);
		glUniform3f(shader->materialAmbient, 1.0f, 0.5f, 0.31f);
	}

	if (shader->materialDiffuse != -1)
	{
		glEnableVertexAttribArray(shader->materialDiffuse);
		glUniform3f(shader->materialDiffuse, 1.0f, 0.5f, 0.31f);
	}

	if (shader->materialShininess != -1)
	{
		glEnableVertexAttribArray(shader->materialShininess);
		glUniform1f(shader->materialShininess, 32.0f);
	}

	if (shader->materialSpecular != -1)
	{
		glEnableVertexAttribArray(shader->materialSpecular);
		glUniform3f(shader->materialSpecular, 0.5f, 0.5f, 0.5f);
	}

	//Lights
	Light *light;
	for (std::map<int, Light*>::iterator i = sm->lights.begin(); i != sm->lights.end(); i++)
	{
		if (i->second->type.compare("directional") == 0)
		{
			light = i->second;
			if (shader->dirLightAmbient != -1)
			{
				glEnableVertexAttribArray(shader->dirLightAmbient);
				glUniform3f(shader->dirLightAmbient, sm->ambientLight->color[0], sm->ambientLight->color[1], sm->ambientLight->color[2]);
			}

			if (shader->dirLightDiffuse != -1)
			{
				glEnableVertexAttribArray(shader->dirLightDiffuse);
				glUniform3f(shader->dirLightDiffuse, light->diffColor[0], light->diffColor[1], light->diffColor[2]);
			}

			if (shader->dirLightDirection != -1)
			{
				glEnableVertexAttribArray(shader->dirLightDirection);
				glUniform3f(shader->dirLightDirection, light->dir[0], light->dir[1], light->dir[2]);
			}


			if (shader->dirLightSpecular != -1)
			{
				glEnableVertexAttribArray(shader->dirLightSpecular);
				glUniform3f(shader->dirLightSpecular, light->specColor[0], light->specColor[1], light->specColor[2]);
			}
		}
		else if (i->second->type.compare("point") == 0)
		{
			light = i->second;
			if (shader->pointLightsAmbient[light->pointID] != -1)
			{
				glEnableVertexAttribArray(shader->pointLightsAmbient[light->pointID]);
				glUniform3f(shader->pointLightsAmbient[light->pointID], sm->ambientLight->color[0], sm->ambientLight->color[1], sm->ambientLight->color[2]);
			}

			if (shader->pointLightsConstant[light->pointID] != -1)
			{
				glEnableVertexAttribArray(shader->pointLightsConstant[light->pointID]);
				glUniform1f(shader->pointLightsConstant[light->pointID], 1.0f);
			}

			if (shader->pointLightsDiffuse[light->pointID] != -1)
			{
				glEnableVertexAttribArray(shader->pointLightsDiffuse[light->pointID]);
				glUniform3f(shader->pointLightsDiffuse[light->pointID], light->diffColor[0], light->diffColor[1], light->diffColor[2]);
			}

			if (shader->pointLightsLinear[light->pointID] != -1)
			{
				glEnableVertexAttribArray(shader->pointLightsLinear[light->pointID]);
				glUniform1f(shader->pointLightsLinear[light->pointID], 0.09f);
			}

			if (shader->pointLightsPosition[light->pointID] != -1)
			{
				if (light->followingObj != -1)
				{
					glEnableVertexAttribArray(shader->pointLightsPosition[light->pointID]);
					glUniform3f(shader->pointLightsPosition[light->pointID], sm->sceneObjects[light->followingObj]->position[0], sm->sceneObjects[light->followingObj]->position[1], sm->sceneObjects[light->followingObj]->position[2]);
				}
				else
				{
					glEnableVertexAttribArray(shader->pointLightsPosition[light->pointID]);
					glUniform3f(shader->pointLightsPosition[light->pointID], light->pos[0], light->pos[1], light->pos[2]);
				}
			}

			if (shader->pointLightsQuadratic[light->pointID] != -1)
			{
				glEnableVertexAttribArray(shader->pointLightsQuadratic[light->pointID]);
				glUniform1f(shader->pointLightsQuadratic[light->pointID], 0.032f);
			}

			if (shader->pointLightsSpecular[light->pointID] != -1)
			{
				glEnableVertexAttribArray(shader->pointLightsSpecular[light->pointID]);
				glUniform3f(shader->pointLightsSpecular[light->pointID], light->specColor[0], light->specColor[1], light->specColor[2]);
			}
		}
		else if (i->second->type.compare("spotlight") == 0)
		{
			light = i->second;

			if (shader->spotLightAmbient != -1)
			{
				glEnableVertexAttribArray(shader->spotLightAmbient);
				glUniform3f(shader->spotLightAmbient, sm->ambientLight->color[0], sm->ambientLight->color[1], sm->ambientLight->color[2]);
			}

			if (shader->spotLightConstant != -1)
			{
				glEnableVertexAttribArray(shader->spotLightConstant);
				glUniform1f(shader->spotLightConstant, 1.0f);
			}


			if (shader->spotLightCutOff != -1)
			{
				glEnableVertexAttribArray(shader->spotLightCutOff);
				glUniform1f(shader->spotLightCutOff, (float)cos(12.5f * PI / 180.0f));
			}

			if (shader->spotLightDiffuse != -1)
			{
				glEnableVertexAttribArray(shader->spotLightDiffuse);
				glUniform3f(shader->spotLightDiffuse, light->diffColor[0], light->diffColor[1], light->diffColor[2]);
			}

			if (shader->spotLightDirection != -1)
			{
				glEnableVertexAttribArray(shader->spotLightDirection);
				glUniform3f(shader->spotLightDirection, light->dir[0], light->dir[1], light->dir[2]);
			}

			if (shader->spotLightLinear != -1)
			{
				glEnableVertexAttribArray(shader->spotLightLinear);
				glUniform1f(shader->spotLightLinear, 1.0f);
			}

			if (shader->spotLightOuterCutOff != -1)
			{
				glEnableVertexAttribArray(shader->spotLightOuterCutOff);
				glUniform1f(shader->spotLightOuterCutOff, (float)cos(15.5f * PI / 180.0f));
			}

			if (shader->spotLightPosition != -1)
			{
				if (light->followingObj != -1)
				{
					glEnableVertexAttribArray(shader->spotLightPosition);
					glUniform3f(shader->spotLightPosition, sm->sceneObjects[light->followingObj]->position[0], sm->sceneObjects[light->followingObj]->position[1], sm->sceneObjects[light->followingObj]->position[2]);
				}
				else
				{
					glEnableVertexAttribArray(shader->spotLightPosition);
					glUniform3f(shader->spotLightPosition, light->pos[0], light->pos[1], light->pos[2]);
				}
			}

			if (shader->spotLightQuadratic != -1)
			{
				glEnableVertexAttribArray(shader->spotLightQuadratic);
				glUniform1f(shader->spotLightQuadratic, 0.032f);
			}

			if (shader->spotLightSpecular != -1)
			{
				glEnableVertexAttribArray(shader->spotLightSpecular);
				glUniform3f(shader->spotLightSpecular, light->specColor[0], light->specColor[1], light->specColor[2]);
			}
		}
	}
}

void SceneObject::Update()
{
	SceneManager *sm = SceneManager::getInstance();

	V = sm->activeCamera->getViewMatrix();
	P = sm->activeCamera->getPerspective();

	sm->activeCamera->unghi[0] -= sm->activeCamera->unghiSpeed[0];
	sm->activeCamera->unghi[1] -= sm->activeCamera->unghiSpeed[1];

	if (sm->activeCamera->unghi[0] > 2 * PI)
	{
	sm->activeCamera->unghi[0] = 0;
	}
	//yaw.SetRotationY(sm->activeCamera->unghi[0]);

	if (sm->activeCamera->unghi[1] > 2 * PI)
	{
	sm->activeCamera->unghi[1] = 0;
	}
	//pitch.SetRotationZ(sm->activeCamera->unghi[1]);

	//yaw.SetRotationY(1.0f * (sm->saved_p.x - sm->current_p.x) / 360);
	//pitch.SetRotationZ(1.0f * (sm->saved_p.y - sm->current_p.y) / 360);

	//scale
	S.SetScale(scale);

	//Translations
	T.SetTranslation((Vector3)position);

	//Rotations
	R.SetRotationX(rotation[0]);

	aux.SetRotationY(rotation[1]);
	R = R * aux;

	aux.SetRotationZ(rotation[2]);
	R = R * aux;

	R = R * pitch * yaw;

	//Model Matrix
	M = S * R * T;
}

void SceneObject::Draw()
{
	SceneManager* sm = SceneManager::getInstance();
	bool debug = SceneManager::getInstance()->debugMode;

	glUseProgram(shader->idProg);

	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);

	if (depthTest) 
	{ 
		glEnable(GL_DEPTH_TEST); 
	}

	if (blend)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	}

	if (wired || debug)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->wiredIboId);
		SendCommonData();

		glDrawElements(GL_LINES, model->nrIndiciWired, GL_UNSIGNED_SHORT, 0);
	}
	else
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboId);
		SendCommonData();

		glDrawElements(GL_TRIANGLES, model->nrIndici, GL_UNSIGNED_SHORT, 0);
	}

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

SceneObject::~SceneObject()
{
}