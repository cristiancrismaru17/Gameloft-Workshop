#pragma once
#include "../Utilities/utilities.h"

struct Trajectory
{
	char *type;
	char *iteration;
	char *direction;
	Vector3 endPoint;
	float speed;
};