#pragma once
#include "ShaderResource.h"
#include "Light.h"
#include "../Utilities/utilities.h"

class Shader
{
public:
	GLuint idProg, vertexShader, fragmentShader;
	GLint positionAttribute;
	GLint colorAttribute;
	GLint transformationMatrix;
	GLint normals;
	GLint projectionMatrix;
	GLint viewMatrix;
	GLint skyColor;
	GLint textureUniform[9];
	GLint cameraPos;
	GLint uniformMatrix;
	GLint uvAttribute;
	GLint uvBlendAttribute;
	GLint uvAlphaAttribute;
	GLint uTime;
	GLint u_DispMax;
	GLint texRatio;
	GLint texRatio2;
	GLint solidColor;

	GLint cellsX;
	GLint cellsY;
	GLint cellSize;


	GLint dirLightDirection;
	GLint dirLightAmbient;
	GLint dirLightDiffuse;
	GLint dirLightSpecular;

	GLint pointLightsPosition[NR_OF_LIGHTS];
	GLint pointLightsAmbient[NR_OF_LIGHTS];
	GLint pointLightsDiffuse[NR_OF_LIGHTS];
	GLint pointLightsSpecular[NR_OF_LIGHTS];
	GLint pointLightsConstant[NR_OF_LIGHTS];
	GLint pointLightsLinear[NR_OF_LIGHTS];
	GLint pointLightsQuadratic[NR_OF_LIGHTS];

	GLint spotLightPosition;
	GLint spotLightDirection;
	GLint spotLightAmbient;
	GLint spotLightDiffuse;
	GLint spotLightSpecular;
	GLint spotLightConstant;
	GLint spotLightLinear;
	GLint spotLightQuadratic;
	GLint spotLightConeAngle;

	GLint materialAmbient;
	GLint materialDiffuse;
	GLint materialSpecular;
	GLint materialShininess;

	ShaderResource* sr;
	~Shader();
	void Load(int id);
};