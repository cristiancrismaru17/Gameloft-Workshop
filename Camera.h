#pragma once
#include "../Utilities/Math.h"
#include "Globals.h"

class Camera {

	public:

		float unghi[2] = { 0.0f, 0.0f };
		float unghiSpeed[2] = { 0.0f, 0.0f };
		bool clockWise[2] = { true, true };

		float sensitivity = 0.1f;

		//Constructori
		Camera();
		Camera(Vector3 position, Vector3 target, Vector3 up, GLfloat moveSpeed, GLfloat rotateSpeed, GLfloat Near, GLfloat Far, GLfloat fov);

		//Getteri
		Vector4 getPosition();
		Vector4 getTarget();
		Vector4 getUp();
		Vector4 getXaxis();
		Vector4 getYaxis();
		Vector4 getZaxiz();
		GLfloat getMoveSpeed();
		GLfloat getRotateSpeed();
		GLfloat getNear();
		GLfloat getFar();
		GLfloat getFov();
		GLfloat getDeltaTime();
		Matrix getViewMatrix();
		Matrix getWorldMatrix();
		Matrix getPerspective();


		//Setteri
		void setPosition(Vector4 position);
		void setTarget(Vector4 target);
		void setUp(Vector4 up);
		void setXaxis(Vector4 xAxis);
		void setYaxis(Vector4 yAxis);
		void setZaxiz(Vector4 zAxis);
		void setTranslationSpeed(GLfloat moveSpeed);
		void setRotationSpeed(GLfloat rotateSpeed);
		void setNear(GLfloat Near);
		void setFar(GLfloat Far);
		void setFov(GLfloat fov);
		void setDeltaTime(GLfloat deltaTime);
		void setViewMatrix(Matrix viewMatrix);
		void setWorldMatrix(Matrix worldMatrix);

		void moveOX(int directie);
		void moveOY(int directie);
		void moveOZ(int directie);
		void rotateOX(int directie);
		void rotateOY(int directie);
		void rotateOZ(int directie);
		void rotateOX(float diff);
		void rotateOY(float diff);
		void rotateOZ(float diff);

		void rotateSceneOX(float diff);
		void rotateSceneOY(float diff);
		void rotateSceneOZ(float diff);

		void updateR();
		void updateWorldView();


	private:
		Vector4 position;
		Vector4 target;
		Vector4 up;
		Vector4 xAxis;
		Vector4 yAxis;
		Vector4 zAxis;
		GLfloat translationSpeed;
		GLfloat rotationSpeed;
		GLfloat Near;
		GLfloat Far;
		GLfloat fov;
		GLfloat deltaTime;
		Matrix viewMatrix;
		Matrix worldMatrix;	
		Matrix R;
		Matrix T;
		Matrix Perspective;

};