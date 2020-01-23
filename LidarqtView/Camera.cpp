#include "Camera.h"
#include <QtCore\qmath.h>

Camera::Camera(QVector3D position, QVector3D up, float yaw, float pitch)
	: Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = QVector3D(posX, posY, posZ);
	WorldUp = QVector3D(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();

}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

QMatrix4x4 Camera::getViewMatrix() const noexcept
{
	QMatrix4x4 viewMatrix;
	viewMatrix.setToIdentity();
	viewMatrix.lookAt(Position, Position + Front, Up);
	return viewMatrix;
}

QVector3D Camera::getCameraPos() const noexcept
{
	return Position;
}

void Camera::updateCameraVectors()
{
	QVector3D front;

	front.setX(cos(qDegreesToRadians(Yaw)) * cos(qDegreesToRadians(Pitch)));
	front.setY(sin(qDegreesToRadians(Pitch)));
	front.setZ(sin(qDegreesToRadians(Yaw)) * cos(qDegreesToRadians(Pitch)));
	Front = front.normalized();

	Right = QVector3D::crossProduct(Front, WorldUp).normalized();
	Up = QVector3D::crossProduct(Right, Front).normalized();
}