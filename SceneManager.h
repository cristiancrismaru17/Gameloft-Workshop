#include <stdio.h>
#include <map>
#include "Camera.h"
#include "Light.h"
#include "SceneObject.h"
#include "AmbientLight.h"
#include "Fire.h"
#include "../Utilities/utilities.h"

class SceneManager
{
private:
	static SceneManager* spInstance; 
public:
	bool debugMode = false;
	POINT current_p, saved_p;
	const float frameLimit = 0.5f;
	float frameTotal;
	void Init(char *fileDir, ESContext *esContext);
	void Draw(ESContext *esContext);
	void Update(ESContext *esContext, float deltaTime);
	static SceneManager* getInstance();
	void freeResources();
	std::map<int, Camera*> cameras;
	Camera *activeCamera;
	std::map<int, SceneObject*> sceneObjects;
	std::map<int, Light*> lights;
	std::map<int, Fire*> fireObjects;
	AmbientLight *ambientLight;
	~SceneManager();
};
