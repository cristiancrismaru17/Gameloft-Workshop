#include "stdafx.h"
#include "Camera.h"

Camera::Camera() {
	setPosition(Vector4(0.0f, 0.0f, -200.0f, 1.0f));
	setTarget(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	setUp(Vector4(0.0f, 1.0f, 0.0f, 0.0f));
	setTranslationSpeed(300.8f);
	setRotationSpeed(0.3f);
	setNear(0.2f);
	setFar(10000);
	setFov(2.0f);

	Perspective.SetPerspective(fov, (GLfloat)Globals::screenWidth / Globals::screenHeight, Near, Far);

	updateWorldView();
}

Camera::Camera(Vector3 position, Vector3 target, Vector3 up, GLfloat moveSpeed, GLfloat rotateSpeed, GLfloat Near, GLfloat Far, GLfloat fov)
{
	setPosition(Vector4(position, 1.0f));
	setTarget(Vector4(target, 1.0f));
	setUp(Vector4(up, 0.0f));
	setTranslationSpeed(moveSpeed);
	setRotationSpeed(rotateSpeed);
	setNear(Near);
	setFar(Far);
	setFov(fov);

	Perspective.SetPerspective(fov, (GLfloat)Globals::screenWidth / Globals::screenHeight, Near, Far);

	updateWorldView();
}

Vector4 Camera::getPosition() {
	return Camera::position;
}

Vector4 Camera::getTarget() {
	return Camera::target;
}

Vector4 Camera::getUp() {
	return up;
}

Vector4 Camera::getXaxis() {
	return Camera::xAxis;
}

Vector4 Camera::getYaxis() {
	return Camera::yAxis;
}

Vector4 Camera::getZaxiz() {
	return Camera::zAxis;
}

GLfloat Camera::getMoveSpeed() {
	return Camera::translationSpeed;
}

GLfloat Camera::getRotateSpeed() {
	return Camera::rotationSpeed;
}

GLfloat Camera::getNear() {
	return Camera::Near;
}

GLfloat Camera::getFar() {
	return Camera::Far;
}

GLfloat Camera::getFov() {
	return Camera::fov;
}

GLfloat Camera::getDeltaTime() {
	return Camera::deltaTime;
}

Matrix Camera::getViewMatrix() {
	return viewMatrix;
}

Matrix Camera::getWorldMatrix() {
	return Camera::worldMatrix;
}

Matrix Camera::getPerspective()
{
	return Perspective;
}

void Camera::setPosition(Vector4 position) {
	Camera::position = position;
}

void Camera::setTarget(Vector4 target) {
	Camera::target = target;
}

void Camera::setUp(Vector4 up) {
	Camera::up = up;
}

void Camera::setXaxis(Vector4 xAxis) {
	Camera::xAxis = xAxis;
}

void Camera::setYaxis(Vector4 yAxis) {
	Camera::yAxis = yAxis;
}

void Camera::setZaxiz(Vector4 zAxis) {
	Camera::zAxis = zAxis;
}

void Camera::setTranslationSpeed(GLfloat moveSpeed) {
	Camera::translationSpeed = moveSpeed;
}

void Camera::setRotationSpeed(GLfloat rotateSpeed) {
	Camera::rotationSpeed = rotateSpeed;
}

void Camera::setNear(GLfloat Near) {
	Camera::Near = Near;
}

void Camera::setFar(GLfloat Far) {
	Camera::Far = Far;
}

void Camera::setFov(GLfloat fov) {
	Camera::fov = fov;
}

void Camera::setDeltaTime(GLfloat deltaTime) {
	Camera::deltaTime = deltaTime;
}

void Camera::setViewMatrix(Matrix viewMatrix) {
	Camera::viewMatrix = viewMatrix;
}

void Camera::setWorldMatrix(Matrix worldMatrix) {
	Camera::worldMatrix = worldMatrix;
}

void Camera::moveOZ(int directie) {
	Vector4 forward;
	Vector4 vectorDeplasare;

	zAxis = -(target - position).Normalize();

	forward = zAxis * (GLfloat)directie;
	vectorDeplasare = forward * translationSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;

	updateWorldView();

}

void Camera::moveOY(int directie) {
	Vector4 forward;
	Vector4 vectorDeplasare;

	forward = up.Normalize() * (GLfloat)directie;
	vectorDeplasare = forward * translationSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;

	updateWorldView();
}

void Camera::moveOX(int directie) {
	updateWorldView();
	Vector4 forward;
	Vector4 vectorDeplasare;

	Vector3 aux = Vector3(zAxis.x, zAxis.y, zAxis.z).Cross(Vector3(yAxis.x, yAxis.y, yAxis.z)).Normalize();
	forward = Vector4(aux.x, aux.y, aux.z, 0) * (GLfloat)directie;

	vectorDeplasare = forward * translationSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;

	updateWorldView();
}

void Camera::rotateOX(int directie) {
	Matrix mRotateOX;
	mRotateOX.SetRotationX(rotationSpeed * deltaTime * directie);

	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 rotatedLocalUp = localUp * mRotateOX;
	up = rotatedLocalUp * worldMatrix;
	up = up.Normalize();

	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;
	target = rotatedTarget * worldMatrix;

	updateWorldView();
}

void Camera::rotateOY(int directie) {
	Matrix mRotateOY;
	mRotateOY.SetRotationY(rotationSpeed * deltaTime * directie);
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOY;
	target = rotatedTarget * worldMatrix;

	updateWorldView();
}

void Camera::rotateOZ(int directie) {
	Matrix mRotateOZ;
	mRotateOZ.SetRotationZ(rotationSpeed * deltaTime * directie);
	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 rotatedUp = localUp * mRotateOZ;
	up = rotatedUp * worldMatrix;

	updateWorldView();
}

void Camera::rotateOX(float diff) {
	Matrix mRotateOX;
	mRotateOX.SetRotationX(sensitivity * diff * deltaTime);

	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 rotatedLocalUp = localUp * mRotateOX;
	up = rotatedLocalUp * worldMatrix;
	up = up.Normalize();

	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;
	target = rotatedTarget * worldMatrix;

	updateWorldView();
}

void Camera::rotateOY(float diff) {
	Matrix mRotateOY;
	mRotateOY.SetRotationY(sensitivity * diff * deltaTime);
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOY;
	target = rotatedTarget * worldMatrix;

	updateWorldView();
}

void Camera::rotateOZ(float diff) {
	Matrix mRotateOZ;
	mRotateOZ.SetRotationZ(diff * deltaTime);
	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 rotatedUp = localUp * mRotateOZ;
	up = rotatedUp * worldMatrix;

	updateWorldView();
}

void Camera::rotateSceneOX(float diff) {
	Matrix mRotateOX;
	mRotateOX.SetRotationAngleAxis(sensitivity * diff * deltaTime, 1.0, 0.0, 0.0);

	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 rotatedLocalUp = localUp * mRotateOX;
	up = rotatedLocalUp * worldMatrix;
	up = up.Normalize();

	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;
	target = rotatedTarget * worldMatrix;

	updateWorldView();
}

void Camera::rotateSceneOY(float diff) {
	Matrix mRotateOY;
	mRotateOY.SetRotationY(sensitivity * diff * deltaTime);

	up = up * mRotateOY;
	up = up.Normalize();

	target -= position;
	target = target * mRotateOY;
	target += position;

	updateWorldView();
}

void Camera::rotateSceneOZ(float diff) {
	Matrix mRotateOZ;
	mRotateOZ.SetRotationAngleAxis(sensitivity * diff * deltaTime, 0.0, 0.0, 1.0);
	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 rotatedUp = localUp * mRotateOZ;
	up = rotatedUp * worldMatrix;

	updateWorldView();
}


void Camera::updateR() {
	R.m[0][0] = xAxis.x;
	R.m[0][1] = xAxis.y;
	R.m[0][2] = xAxis.z;
	R.m[0][3] = 0;

	R.m[1][0] = yAxis.x;
	R.m[1][1] = yAxis.y;
	R.m[1][2] = yAxis.z;
	R.m[1][3] = 0;

	R.m[2][0] = zAxis.x;
	R.m[2][1] = zAxis.y;
	R.m[2][2] = zAxis.z;
	R.m[2][3] = 0;

	R.m[3][0] = 0;
	R.m[3][1] = 0;
	R.m[3][2] = 0;
	R.m[3][3] = 1;
}

void Camera::updateWorldView() {
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();

	Vector3 aux = Vector3(zAxis.x, zAxis.y, zAxis.z).Cross(Vector3(yAxis.x, yAxis.y, yAxis.z)).Normalize();
	xAxis = Vector4(aux.x, aux.y, aux.z, 0);

	updateR();

	T.SetTranslation(position.x, position.y, position.z);
	worldMatrix = R*T;
	viewMatrix = T.SetTranslation(-position.x, -position.y, -position.z) * R.Transpose();
}