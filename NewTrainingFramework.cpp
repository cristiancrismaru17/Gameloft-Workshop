#include "stdafx.h"
#include "Globals.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "../Utilities/utilities.h"

using namespace std;

void Init ( ESContext *esContext )
{
	ResourceManager::getInstance()->Init("resourceManager.xml");
	SceneManager::getInstance()->Init("sceneManager.xml", esContext);
}

void Draw(ESContext *esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SceneManager::getInstance()->Draw(esContext);
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime )
{
	SceneManager::getInstance()->Update(esContext, deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		switch (key) {
			case 'W':  SceneManager::getInstance()->activeCamera->moveOZ(-1); break;
			case 'S':  SceneManager::getInstance()->activeCamera->moveOZ(1); break;
			case 'A':  SceneManager::getInstance()->activeCamera->moveOX(-1); break;
			case 'D':  SceneManager::getInstance()->activeCamera->moveOX(1); break;
			case 'Z':  SceneManager::getInstance()->activeCamera->moveOY(-1); break;
			case 'X':  SceneManager::getInstance()->activeCamera->moveOY(1); break;
			case 'Y':  SceneManager::getInstance()->activeCamera->rotateOZ(-1); break;
			case 'R':  SceneManager::getInstance()->activeCamera->rotateOZ(1); break;
			case 'G':  SceneManager::getInstance()->activeCamera->rotateOX(-1); break;
			case 'T':  SceneManager::getInstance()->activeCamera->rotateOX(1); break;
			case 'H':  SceneManager::getInstance()->activeCamera->rotateOY(-1); break;
			case 'F':  SceneManager::getInstance()->activeCamera->rotateOY(1); break;
			case 'L':  SceneManager::getInstance()->debugMode = !(SceneManager::getInstance()->debugMode); break;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Game engine", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	Init( &esContext );

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	//....

	printf("Press any key...\n");
	_getch();

	
	return 0;
}

