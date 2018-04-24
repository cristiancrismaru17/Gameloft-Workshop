#pragma once
#include "ShaderResource.h"
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

	GLint dirLightDirection;
	GLint dirLightAmbient;
	GLint dirLightDiffuse;
	GLint dirLightSpecular;

	GLint pointLights0Position;
	GLint pointLights0Ambient;
	GLint pointLights0Diffuse;
	GLint pointLights0Specular;
	GLint pointLights0Constant;
	GLint pointLights0Linear;
	GLint pointLights0Quadratic;

	GLint pointLights1Position;
	GLint pointLights1Ambient;
	GLint pointLights1Diffuse;
	GLint pointLights1Specular;
	GLint pointLights1Constant;
	GLint pointLights1Linear;
	GLint pointLights1Quadratic;
	
	GLint pointLights2Position;
	GLint pointLights2Ambient;
	GLint pointLights2Diffuse;
	GLint pointLights2Specular;
	GLint pointLights2Constant;
	GLint pointLights2Linear;
	GLint pointLights2Quadratic;

	GLint pointLights3Position;
	GLint pointLights3Ambient;
	GLint pointLights3Diffuse;
	GLint pointLights3Specular;
	GLint pointLights3Constant;
	GLint pointLights3Linear;
	GLint pointLights3Quadratic;

	GLint spotLightPosition;
	GLint spotLightDirection;
	GLint spotLightAmbient;
	GLint spotLightDiffuse;
	GLint spotLightSpecular;
	GLint spotLightConstant;
	GLint spotLightLinear;
	GLint spotLightQuadratic;
	GLint spotLightCutOff;
	GLint spotLightOuterCutOff;

	GLint materialAmbient;
	GLint materialDiffuse;
	GLint materialSpecular;
	GLint materialShininess;

	ShaderResource* sr;
	~Shader();
	void Load(int id);
};