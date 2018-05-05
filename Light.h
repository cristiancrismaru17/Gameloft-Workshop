#pragma once
#include <string>
#include "../Utilities/utilities.h"
#define NR_OF_LIGHTS 10

struct Light
{
	std::string type;

	int followingObj = -1;
	int pointID = 0;
	Vector3 pos;
	Vector3 dir;
	Vector3 color;
	Vector3 specColor;
	Vector3 diffColor;
};
