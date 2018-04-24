#pragma once
#include <stdio.h>
#include <map>
#include <string>
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "FollowingCamera.h"
#include "Trajectory.h"
#include "../Utilities/utilities.h"

class SceneObject
{
public:
	//proprietati necesare
	virtual void Draw();
	virtual void Update();
	void SendCommonData();
	std::string type;
	int id;
	Vector3 position;
	Vector3 rotation;
	Vector3 color;
	Vector3 scale;
	Model *model;
	Shader *shader;
	std::map<int ,Texture *> textures;
	bool depthTest = false;
	bool blend = true;
	bool wired = false;

	Matrix pitch, yaw, aux;
	Matrix V, P, M, S, R, T;

	//proprietati optionale
	std::string name;
	float selfrotatespeed;
	int *lightIds;
	FollowingCamera *followingCamera;
	SceneObject();
	~SceneObject();
};