#pragma once
#include "Vertex.h"
#include <vector>
#include "ModelResource.h"
#include "../Utilities/utilities.h"

class Model
{
public:
	int nrVertecsi;
	int nrIndici;
	int nrIndiciWired;
	ModelResource* mr;
	GLuint iboId;
	GLuint wiredIboId;
	GLuint vboId;
	GLushort *indices;
	GLushort *wfIndices;
	Vertex *vertices;
	void Load(int id);
	void LoadTerrain(int id);
	void terrainTranslateX(int dir);
	void terrainTranslateZ(int dir);
	~Model();
};