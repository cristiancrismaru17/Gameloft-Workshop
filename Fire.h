#pragma once
#include "SceneObject.h"
class Fire :
	public SceneObject
{
public:
	float uTime;
	float u_DispMax;
	Fire();
	void Draw();
	void Update();
	void Init();
	~Fire();
	float maxDisp;
};

