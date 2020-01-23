#pragma once

#include <QtGui\qvector3d.h>
#include <QtGui\qmatrix4x4.h>
#include <QtGui\qopenglshaderprogram.h>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 7.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	QVector3D Position;
	QVector3D Front;
	QVector3D Up;
	QVector3D Right;
	QVector3D WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(QVector3D position = QVector3D(0.0f, 0.0f, 0.0f), QVector3D up = QVector3D(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void ProcessMouseScroll(float yoffset);
	QMatrix4x4 getViewMatrix() const noexcept;
	QVector3D getCameraPos() const noexcept;
private:
	void updateCameraVectors();
};