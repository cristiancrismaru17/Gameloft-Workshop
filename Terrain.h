#pragma once
#include "SceneObject.h"


class Terrain :
	public SceneObject
{
public:
	int horizontalCells;
	int verticalCells;
	float cellSize;
	float offsetY;
	Trajectory *trajectory;
	Vector3 color;
	void Draw();
	void Update();
	void Init();
	Terrain();
	~Terrain();
};

