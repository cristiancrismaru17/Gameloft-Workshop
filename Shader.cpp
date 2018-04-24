#include "stdafx.h"
#include "Shader.h"
#include <stdio.h>
#include <string>
#include "ResourceManager.h"
#include "../Utilities/utilities.h"

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

	pointLights0Ambient = glGetUniformLocation(idProg, "pointLights[0].ambient");
	pointLights0Constant = glGetUniformLocation(idProg, "pointLights[0].constant");
	pointLights0Diffuse = glGetUniformLocation(idProg, "pointLights[0].diffuse");
	pointLights0Linear = glGetUniformLocation(idProg, "pointLights[0].linear");
	pointLights0Position = glGetUniformLocation(idProg, "pointLights[0].position");
	pointLights0Quadratic = glGetUniformLocation(idProg, "pointLights[0].quadratic");
	pointLights0Specular = glGetUniformLocation(idProg, "pointLights[0].specular");
	
	pointLights1Ambient = glGetUniformLocation(idProg, "pointLights[1].ambient");
	pointLights1Constant = glGetUniformLocation(idProg, "pointLights[1].constant");
	pointLights1Diffuse = glGetUniformLocation(idProg, "pointLights[1].diffuse");
	pointLights1Linear = glGetUniformLocation(idProg, "pointLights[1].linear");
	pointLights1Position = glGetUniformLocation(idProg, "pointLights[1].position");
	pointLights1Quadratic = glGetUniformLocation(idProg, "pointLights[1].quadratic");
	pointLights1Specular = glGetUniformLocation(idProg, "pointLights[1].specular");

	pointLights2Ambient = glGetUniformLocation(idProg, "pointLights[2].ambient");
	pointLights2Constant = glGetUniformLocation(idProg, "pointLights[2].constant");
	pointLights2Diffuse = glGetUniformLocation(idProg, "pointLights[2].diffuse");
	pointLights2Linear = glGetUniformLocation(idProg, "pointLights[2].linear");
	pointLights2Position = glGetUniformLocation(idProg, "pointLights[2].position");
	pointLights2Quadratic = glGetUniformLocation(idProg, "pointLights[2].quadratic");
	pointLights2Specular = glGetUniformLocation(idProg, "pointLights[2].specular");

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
