#include "stdafx.h"
#include "Skybox.h"
#include "SceneManager.h"


Skybox::Skybox()
{
}

void Skybox::Update()
{
	SceneManager *sm = SceneManager::getInstance();
	
	V = sm->activeCamera->getViewMatrix();
	P = sm->activeCamera->getPerspective();

	//yaw.SetRotationY(1.0f * (sm->saved_p.x - sm->current_p.x) / 360);
	//pitch.SetRotationZ(1.0f * (sm->saved_p.y - sm->current_p.y) / 360);

	//scale
	S.SetScale(scale);

	//Translations
	T.SetTranslation(Vector3(0, offsetY, 0));

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

Skybox::~Skybox()
{
}
