#pragma once
#include "SceneObject.h"


class Skybox : public SceneObject
{
public:
	float offsetY;
	Skybox();
	void Update();
	~Skybox();
};
