#include "stdafx.h"
#include "Fire.h"
#include "SceneManager.h"


Fire::Fire()
{
}

void Fire::Init()
{
	uTime = 0.0f;
	SceneManager *sm = SceneManager::getInstance();

	V = sm->activeCamera->getViewMatrix();
	P = sm->activeCamera->getPerspective();

	T.SetIdentity();

	//scale
	S.SetScale(scale);

	//Translations
	T.SetTranslation(position);
	M = S * T;
}

void Fire::Draw()
{
	SceneManager* sm = SceneManager::getInstance();
	Fire *fo; fo = (Fire *)sm->fireObjects[id];
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
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

		float hRatio = 1.0f * textures[10]->tHeight / textures[11]->tHeight;
		float wRatio = 1.0f * textures[10]->tWidth / textures[11]->tWidth;
		float hRatio2 = 1.0f * textures[10]->tHeight / textures[9]->tHeight;
		float wRatio2 = 1.0f * textures[10]->tWidth / textures[9]->tWidth;

		//uvblend
		if (shader->uvBlendAttribute != -1)
		{
			glEnableVertexAttribArray(shader->uvBlendAttribute);
			glVertexAttribPointer(shader->uvBlendAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(5 * sizeof(Vector3) + sizeof(Vector2)));
		}
		if (shader->uvAlphaAttribute != -1)
		{
			glEnableVertexAttribArray(shader->uvAlphaAttribute);
			glVertexAttribPointer(shader->uvAlphaAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(5 * sizeof(Vector3) + 2 * sizeof(Vector2)));
		}
		if (shader->texRatio != -1)
		{
			glEnableVertexAttribArray(shader->texRatio);
			glUniform2f(shader->texRatio, wRatio, hRatio);
		}
		if (shader->texRatio2 != -1)
		{
			glEnableVertexAttribArray(shader->texRatio2);
			glUniform2f(shader->texRatio2, wRatio2, hRatio2);
		}
		if (shader->u_DispMax != -1)
		{
			glEnableVertexAttribArray(shader->u_DispMax);
			glUniform1f(shader->u_DispMax, u_DispMax);
		}
		if (shader->uTime != -1)
		{
			glEnableVertexAttribArray(shader->uTime);
			glUniform1f(shader->uTime, uTime);
		}

		glDrawElements(GL_TRIANGLES, model->nrIndici, GL_UNSIGNED_SHORT, 0);
	}

	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Fire::Update()
{
	SceneManager *sm = SceneManager::getInstance();

	V = sm->activeCamera->getViewMatrix();
	P = sm->activeCamera->getPerspective();

	u_DispMax = 0.07f;

	uTime += 0.007f;

	if (uTime >= 1.0f)
	{
		uTime = 0.0f;
	}
}

Fire::~Fire()
{
}
