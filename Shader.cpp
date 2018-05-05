#include "stdafx.h"
#include "Shader.h"
#include <stdio.h>
#include <string>
#include "ResourceManager.h"
#include "../Utilities/utilities.h"

std::string PointAmbient(int i)
{
	std::string s;
	s.assign("pointLights[");

	char nr[11];
	_itoa(i, nr, 10);

	s.append(nr);
	s.append("].ambient");

	return s;
}
std::string PointConstant(int i)
{
	std::string s;
	s.assign("pointLights[");

	char nr[11];
	_itoa(i, nr, 10);

	s.append(nr);
	s.append("].constant");

	return s;
}
std::string PointLinear(int i)
{
	std::string s;
	s.assign("pointLights[");

	char nr[11];
	_itoa(i, nr, 10);

	s.append(nr);
	s.append("].Linear");

	return s;
}
std::string PointQuadratic(int i)
{
	std::string s;
	s.assign("pointLights[");

	char nr[11];
	_itoa(i, nr, 10);

	s.append(nr);
	s.append("].quadratic");

	return s;
}
std::string PointDiffuse(int i)
{
	std::string s;
	s.assign("pointLights[");

	char nr[11];
	_itoa(i, nr, 10);

	s.append(nr);
	s.append("].diffuse");

	return s;
}
std::string PointSpecular(int i)
{
	std::string s;
	s.assign("pointLights[");

	char nr[11];
	_itoa(i, nr, 10);

	s.append(nr);
	s.append("].specular");

	return s;
}
std::string PointPosition(int i)
{
	std::string s;
	s.assign("pointLights[");

	char nr[11];
	_itoa(i, nr, 10);

	s.append(nr);
	s.append("].position");

	return s;
}

void Shader::Load(int id)
{
	sr = ResourceManager::getInstance()->pShaderResource[id];

	char* cvstr = new char[sr->vs.length() + 1];
	strcpy(cvstr, sr->vs.c_str());


	vertexShader = esLoadShader(GL_VERTEX_SHADER, cvstr);

	if (vertexShader == 0)
		throw "VERTEX SHADER ERROR";

	char* cfstr = new char[sr->fs.length() + 1];
	strcpy(cfstr, sr->fs.c_str());

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, cfstr);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		throw "FRAGMENT SHADER ERROR";
	}

	idProg = esLoadProgram(vertexShader, fragmentShader);
	positionAttribute = glGetAttribLocation(idProg, "a_posL");
	colorAttribute = glGetAttribLocation(idProg, "a_color");
	uvAttribute = glGetAttribLocation(idProg, "a_uv");
	uvBlendAttribute = glGetAttribLocation(idProg, "a_buv");
	uvAlphaAttribute = glGetAttribLocation(idProg, "a_auv");
	uTime = glGetUniformLocation(idProg, "uTime");
	u_DispMax = glGetUniformLocation(idProg, "u_DispMax");
	normals = glGetAttribLocation(idProg, "a_normals");
	transformationMatrix = glGetUniformLocation(idProg, "transformationMatrix");
	projectionMatrix = glGetUniformLocation(idProg, "projectionMatrix");
	viewMatrix = glGetUniformLocation(idProg, "viewMatrix");
	textureUniform[0] = glGetUniformLocation(idProg, "u_texture0");
	textureUniform[1] = glGetUniformLocation(idProg, "u_texture1");
	textureUniform[2] = glGetUniformLocation(idProg, "u_texture2");
	textureUniform[3] = glGetUniformLocation(idProg, "u_texture3");
	textureUniform[4] = glGetUniformLocation(idProg, "u_texture4");
	textureUniform[5] = glGetUniformLocation(idProg, "u_texture5");
	textureUniform[6] = glGetUniformLocation(idProg, "u_texture6");
	textureUniform[7] = glGetUniformLocation(idProg, "u_texture7");
	textureUniform[8] = glGetUniformLocation(idProg, "u_texture8");
	texRatio = glGetUniformLocation(idProg, "texRatio");
	texRatio2 = glGetUniformLocation(idProg, "texRatio2");
	cameraPos = glGetUniformLocation(idProg, "cameraPos");
	skyColor = glGetUniformLocation(idProg, "skyColor");
	solidColor = glGetUniformLocation(idProg, "solidColor");

	dirLightAmbient = glGetUniformLocation(idProg, "dirLight.ambient");
	dirLightDiffuse = glGetUniformLocation(idProg, "dirLight.diffuse");
	dirLightDirection = glGetUniformLocation(idProg, "dirLight.direction");
	dirLightSpecular = glGetUniformLocation(idProg, "dirLight.specular");

	for (int i = 0; i < NR_OF_LIGHTS ; i++)
	{
		pointLightsAmbient[i] = glGetUniformLocation(idProg, PointAmbient(i).c_str());
		pointLightsDiffuse[i] = glGetUniformLocation(idProg, PointDiffuse(i).c_str());
		pointLightsPosition[i] = glGetUniformLocation(idProg, PointPosition(i).c_str());
		pointLightsSpecular[i] = glGetUniformLocation(idProg, PointSpecular(i).c_str());
		pointLightsConstant[i] = glGetUniformLocation(idProg, PointConstant(i).c_str());
		pointLightsQuadratic[i] = glGetUniformLocation(idProg, PointQuadratic(i).c_str());
		pointLightsLinear[i] = glGetUniformLocation(idProg, PointLinear(i).c_str());
	}

	spotLightAmbient = glGetUniformLocation(idProg, "spotLight.ambient");
	spotLightConstant = glGetUniformLocation(idProg, "spotLight.constant");
	spotLightCutOff = glGetUniformLocation(idProg, "spotLight.cutOff");
	spotLightDiffuse = glGetUniformLocation(idProg, "spotLight.diffuse");
	spotLightDirection = glGetUniformLocation(idProg, "spotLight.direction");
	spotLightLinear = glGetUniformLocation(idProg, "spotLight.linear");
	spotLightOuterCutOff = glGetUniformLocation(idProg, "spotLight.outerCutOff");
	spotLightPosition = glGetUniformLocation(idProg, "spotLight.position");
	spotLightQuadratic = glGetUniformLocation(idProg, "spotLight.quadratic");
	spotLightSpecular = glGetUniformLocation(idProg, "spotLight.specular");

	materialAmbient = glGetUniformLocation(idProg, "material.ambient");
	materialDiffuse = glGetUniformLocation(idProg, "material.diffuse");
	materialShininess = glGetUniformLocation(idProg, "material. shininess");
	materialSpecular = glGetUniformLocation(idProg, "material.specular");
}

Shader::~Shader()
{
	glDeleteProgram(idProg);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
