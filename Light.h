#pragma once
#include <string>
#include <stdio.h>
#include "../Utilities/utilities.h"

#ifndef NR_OF_LIGHTS
#define NR_OF_LIGHTS 10
#endif // !NR_OF_LIGHTS

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
	float coneAngle;
};