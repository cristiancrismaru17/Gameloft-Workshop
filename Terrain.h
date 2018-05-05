#pragma once
#include "SceneObject.h"


class Terrain : public SceneObject
{
private:
	int countX = 0;
	int countZ = 0;
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

