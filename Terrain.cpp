#include "stdafx.h"
#include "Terrain.h"
#include "Shader.h"
#include "SceneObject.h"
#include "SceneManager.h"
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
	T.SetTranslation(Vector3((sm->activeCamera->getPosition()[0] - (horizontalCells * cellSize / 2) * scale[0]),
		sm->activeCamera->getPosition()[1] + offsetY * scale[1],
		(sm->activeCamera->getPosition()[2] - (verticalCells * cellSize / 2) * scale[2])));
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

	V = sm->activeCamera->getViewMatrix();
	P = sm->activeCamera->getPerspective();
}

Terrain::~Terrain()
{
}
