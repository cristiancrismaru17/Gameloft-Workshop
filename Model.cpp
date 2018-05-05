#include "stdafx.h"
#include <string>
#include <stdio.h>
#include "Vertex.h"
#include "Model.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Terrain.h"
#include "../Utilities/utilities.h"


void Model::Load(int id)
{
	mr = ResourceManager::getInstance()->pModelResource[id];
	std::ifstream f(mr->path);

	std::string s;

	if (f.is_open() == false)
	{
		throw("File not opened!\n");
	}

	// Vertices
	getline(f, s, ' ');
	getline(f, s);
	nrVertecsi = atoi(s.c_str());

	vertices = new Vertex[nrVertecsi];

	for (int i = 0; i < nrVertecsi; i++) {
		//pos
		getline(f, s, '[');
		getline(f, s, ',');
		vertices[i].pos.x = (float)atof(s.c_str());

		getline(f, s, ' ');
		getline(f, s, ',');
		vertices[i].pos.y = (float)atof(s.c_str());

		getline(f, s, ' ');
		getline(f, s, ']');
		vertices[i].pos.z = (float)atof(s.c_str());

		//norm
		getline(f, s, '[');
		getline(f, s, ',');
		vertices[i].norm.x = (float)atof(s.c_str());

		getline(f, s, ' ');
		getline(f, s, ',');
		vertices[i].norm.y = (float)atof(s.c_str());

		getline(f, s, ' ');
		getline(f, s, ']');
		vertices[i].norm.z = (float)atof(s.c_str());

		//binorm
		getline(f, s, '[');
		getline(f, s, ',');
		vertices[i].binorm.x = (float)atof(s.c_str());

		getline(f, s, ' ');
		getline(f, s, ',');
		vertices[i].binorm.y = (float)atof(s.c_str());

		getline(f, s, ' ');
		getline(f, s, ']');
		vertices[i].binorm.z = (float)atof(s.c_str());

		//tgt
		getline(f, s, '[');
		getline(f, s, ',');
		vertices[i].tgt.x = (float)atof(s.c_str());

		getline(f, s, ' ');
		getline(f, s, ',');
		vertices[i].tgt.y = (float)atof(s.c_str());

		getline(f, s, ' ');
		getline(f, s, ']');
		vertices[i].tgt.z = (float)atof(s.c_str());

		//uv
		getline(f, s, '[');
		getline(f, s, ',');
		vertices[i].uv.x = (float)atof(s.c_str());

		getline(f, s, ' ');
		getline(f, s, ']');
		vertices[i].uv.y = (float)atof(s.c_str());

		s.assign("");
	}

	//Indexes
	getline(f, s, ' ');
	getline(f, s, '\n');
	nrIndici = atoi((char *)s.c_str());

	indices = new GLushort[nrIndici];

	for (int i = 0; i < (nrIndici / 3); i++) {
		getline(f, s, '.');
		getline(f, s, ' ');
		while (s != "") {
			getline(f, s, ' ');
		}
		getline(f, s, ',');
		indices[i * 3 + 0] = atoi((char *)s.c_str());

		getline(f, s, ' ');
		while (s != "") {
			getline(f, s, ' ');
		}
		getline(f, s, ',');
		indices[i * 3 + 1] = atoi((char *)s.c_str());

		getline(f, s, ' ');
		while (s != "") {
			getline(f, s, ' ');
		}
		getline(f, s, '\n');
		indices[i * 3 + 2] = atoi((char *)s.c_str());
	}
	
	nrIndiciWired = 2 * nrIndici;

	wfIndices = new GLushort[nrIndiciWired];

	int k = 0;
	for (int i = 0; i < nrIndici; i += 3)
	{
		wfIndices[k++] = indices[i];
		wfIndices[k++] = indices[i + 1];
		wfIndices[k++] = indices[i + 1];
		wfIndices[k++] = indices[i + 2];
		wfIndices[k++] = indices[i + 2];
		wfIndices[k++] = indices[i];
	}

	glGenBuffers(1, &vboId); 
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, nrVertecsi * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &wiredIboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wiredIboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndiciWired * sizeof(GLushort), wfIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndici * sizeof(GLushort), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	f.close();
}

void Model::LoadTerrain(int id)
{
	Terrain *to;
	to = (Terrain *)SceneManager::getInstance()->sceneObjects[id];

	nrVertecsi = ((to->verticalCells + 1) * (to->horizontalCells + 1));
	nrIndici = (to->verticalCells * to->horizontalCells) * 6;

	vertices = new Vertex[nrVertecsi];

	int k = 0;
	for (int i = 0; i < (to->verticalCells + 1); i++)
	{
		for (int j = 0; j < (to->horizontalCells + 1); j++)
		{
			vertices[k].pos.x = to->cellSize * j;
			vertices[k].pos.y = to->offsetY;
			vertices[k].pos.z = to->cellSize * i;
			vertices[k].uv = Vector2((GLfloat)i, (GLfloat)j);
			vertices[k].uvBlend = Vector2(1.0f * i / to->verticalCells, 1.0f * j / to->horizontalCells);
			k++;
		}
	}

	indices = new GLushort[nrIndici];

	k = 0;
	for (int i = 0; i < to->verticalCells; i++)
	{
		for (int j = 0; j < to->horizontalCells; j++)
		{
			indices[k * 6 + 0] = (to->horizontalCells + 1) * i + j;
			indices[k * 6 + 1] = (to->horizontalCells + 1) * i + j + 1;
			indices[k * 6 + 2] = (to->horizontalCells + 1) * (i + 1) + j;
			indices[k * 6 + 3] = (to->horizontalCells + 1) * i + j + 1;
			indices[k * 6 + 4] = (to->horizontalCells + 1) * (i + 1) + j;
			indices[k * 6 + 5] = (to->horizontalCells + 1) * (i + 1) + j + 1;
			k++;
		}
	}

	/*for (int i = 0; i < (to->verticalCells * to->horizontalCells) * 6; i++)
	{
		printf("indices[%d] = %d\n", i, indices[i]);
	}*/

	nrIndiciWired = 2 * nrIndici;

	wfIndices = new GLushort[nrIndiciWired];

	k = 0;
	for (int i = 0; i < nrIndici; i+=3)
	{
		wfIndices[k++] = indices[i];
		wfIndices[k++] = indices[i + 1];
		wfIndices[k++] = indices[i + 1];
		wfIndices[k++] = indices[i + 2];
		wfIndices[k++] = indices[i + 2];
		wfIndices[k++] = indices[i];
	}

	/*for (int i = 0; i < nrIndiciWired; i++)
	{
		printf("wfindices[%d] = %d\n", i, wfIndices[i]);
	}*/

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, nrVertecsi * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &wiredIboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wiredIboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndiciWired * sizeof(GLushort), wfIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndici * sizeof(GLushort), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::terrainTranslateZ(int dir)
{
	ResourceManager * rm = ResourceManager::getInstance();
	Terrain * to;
	to = (Terrain *)SceneManager::getInstance()->sceneObjects[5];

	Vector2 * aux;
	aux = (Vector2 *)calloc(to->horizontalCells, sizeof(Vector2));

	if (dir > 0)
	{

		int k = 0;
		for (int i = 0; i < to->horizontalCells + 1; i++)
		{
			aux[i] = rm->models[5]->vertices[k].uvBlend;
			k++;
		}

		k = 0;
		for (int i = 0; i < to->verticalCells; i++)
		{
			for (int j = 0; j < to->horizontalCells + 1; j++)
			{
				rm->models[5]->vertices[k].uvBlend = rm->models[5]->vertices[k + to->horizontalCells + 1].uvBlend;
				k++;
			}
		}

		k = (to->verticalCells) * (to->horizontalCells + 1);
		for (int i = 0; i < to->horizontalCells + 1; i++)
		{
			rm->models[5]->vertices[k].uvBlend = aux[i];
			k++;
		}
	}
	else
	{
		int k = (to->verticalCells) * (to->horizontalCells + 1);
		for (int i = 0; i < to->horizontalCells + 1; i++)
		{
			aux[i] = rm->models[5]->vertices[k].uvBlend;
			k++;
		}

		k = (to->verticalCells + 1) * (to->horizontalCells + 1) - 1;
		for (int g = to->verticalCells; g >= 0; g--)
		{
			for (int r = to->horizontalCells; r > 0; r--)
			{
				rm->models[5]->vertices[k].uvBlend = rm->models[5]->vertices[k - to->horizontalCells - 1].uvBlend;
				k--;
			}
		}

		k = 0;
		for (int i = 0; i < to->horizontalCells + 1; i++)
		{
			rm->models[5]->vertices[k].uvBlend = aux[i];
			k++;
		}
	}

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, nrVertecsi * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Model::terrainTranslateX(int dir)
{
	ResourceManager * rm = ResourceManager::getInstance();
	Terrain * to;
	to = (Terrain *)SceneManager::getInstance()->sceneObjects[5];

	Vector2 * aux;
	aux = (Vector2 *)calloc(to->horizontalCells, sizeof(Vector2));

	if (dir > 0)
	{
		for (int i = 0; i < to->verticalCells + 1; i++)
		{
			aux[i] = rm->models[5]->vertices[i * (to->horizontalCells + 1)].uvBlend;
		}

		for (int i = 0; i < to->horizontalCells; i++)
		{
			for (int j = 0; j < to->verticalCells + 1; j++)
			{
				rm->models[5]->vertices[i + j * (to->horizontalCells + 1)].uvBlend = rm->models[5]->vertices[i + j * (to->horizontalCells + 1) + 1].uvBlend;
			}
		}

		int k = to->horizontalCells;
		for (int i = 0; i < to->verticalCells + 1; i++)
		{
			rm->models[5]->vertices[k].uvBlend = aux[i];
			k += to->horizontalCells + 1;
		}
	}
	else
	{

		for (int i = 0; i < to->verticalCells + 1; i++)
		{
			aux[i] = rm->models[5]->vertices[i * (to->horizontalCells + 1) + to->horizontalCells].uvBlend;
		}

		for (int i = to->horizontalCells; i > 0; i--)
		{
			for (int j = to->verticalCells; j >= 0; j--)
			{
				rm->models[5]->vertices[i + j * (to->horizontalCells + 1)].uvBlend = rm->models[5]->vertices[i + j * (to->horizontalCells + 1) - 1].uvBlend;
			}
		}

		for (int i = 0; i < to->verticalCells + 1; i++)
		{
			rm->models[5]->vertices[i * (to->horizontalCells + 1)].uvBlend = aux[i];
		}
	}

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, nrVertecsi * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Model::~Model()
{
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &wiredIboId);
	glDeleteBuffers(1, &iboId);
	delete &nrVertecsi, &nrIndici, &nrIndiciWired, &vertices, &indices, &wfIndices;
	delete &mr;
}
