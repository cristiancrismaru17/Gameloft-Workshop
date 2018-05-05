#include "stdafx.h"
#include "Terrain.h"
#include "Shader.h"
#include "Model.h"
#include "SceneObject.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "../Utilities/utilities.h"


Terrain::Terrain()
{
}

void Terrain::Init()
{
	SceneManager *sm = SceneManager::getInstance();

	V = sm->activeCamera->getViewMatrix();
	P = sm->activeCamera->getPerspective();

	T.SetIdentity();

	//scale
	S.SetScale(scale);

	//Translations
	position = Vector3((sm->activeCamera->getPosition()[0] - (horizontalCells * cellSize / 2) * scale[0]),
		sm->activeCamera->getPosition()[1] + offsetY * scale[1],
		(sm->activeCamera->getPosition()[2] - (verticalCells * cellSize / 2) * scale[2]));
		T.SetTranslation(position);
	M = S * T;
}

void Terrain::Draw()
{
	SceneManager* sm = SceneManager::getInstance();
	Terrain *to; to = (Terrain *)sm->sceneObjects[5];
	bool debug = SceneManager::getInstance()->debugMode;

	glUseProgram(shader->idProg);

	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);

	if (depthTest) { glEnable(GL_DEPTH_TEST); }

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

		if (shader->cellsX != -1)
		{
			glEnableVertexAttribArray(shader->cellsX);
			glUniform1f(shader->cellsX, (float)to->horizontalCells);
		}
		if (shader->cellsY != -1)
		{
			glEnableVertexAttribArray(shader->cellsY);
			glUniform1f(shader->cellsY, (float)to->verticalCells);
		}
		if (shader->cellSize != -1)
		{
			glEnableVertexAttribArray(shader->cellSize);
			glUniform1f(shader->cellSize, to->cellSize);
		}

		//uvblend
		if (shader->uvBlendAttribute != -1)
		{
			glEnableVertexAttribArray(shader->uvBlendAttribute);
			glVertexAttribPointer(shader->uvBlendAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(5 * sizeof(Vector3) + sizeof(Vector2)));
		}

		glDrawElements(GL_TRIANGLES, model->nrIndici, GL_UNSIGNED_SHORT, 0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Terrain::Update()
{
	SceneManager *sm = SceneManager::getInstance();
	ResourceManager *rm = ResourceManager::getInstance();
	Camera * cm = sm->activeCamera;

	V = sm->activeCamera->getViewMatrix();
	P = sm->activeCamera->getPerspective();

	Matrix T1;
	T1.SetTranslation(position);

	if (cm->getPosition().x > M.m[3][0] + (cellSize * horizontalCells * scale.x * 0.6f))
	{
		countX++;
		rm->models[id]->terrainTranslateX(1);
	}
	else if (cm->getPosition().x < M.m[3][0] + (cellSize * horizontalCells * scale.x * 0.4f))
	{
		countX--;
		rm->models[id]->terrainTranslateX(-1);
	}

	if (cm->getPosition().z > M.m[3][2] + (cellSize * verticalCells * scale.z * 0.6f))
	{
		countZ++;
		rm->models[id]->terrainTranslateZ(1);
	}
	else if (cm->getPosition().z < M.m[3][2] + (cellSize * verticalCells * scale.z * 0.4f))
	{
		countZ--;
		rm->models[id]->terrainTranslateZ(-1);
	}

	T.SetTranslation(countX * cellSize, 0.0, countZ * cellSize);
	T1 = T * T1;

	M = S * T1;
}

Terrain::~Terrain()
{
}
