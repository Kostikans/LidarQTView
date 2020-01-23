#pragma once
#include <GL\glew.h>
#include <QtWidgets\qwidget.h>
#include <QtWidgets\qopenglwidget.h>
#include <QtGui\qvector3d.h>
#include <QtGui\qmatrix4x4.h>
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexAttribBuffer.h"
#include "Camera.h"
#include "LasParsing.h"
#include <QtGui\qevent.h>
#include <QtCore\qobject.h>
#include <QtCore\qvector.h>
#include <QtGui\qopenglvertexarrayobject.h>
#include <QtGui\qquaternion.h>

class LidarViewWidget : public  QOpenGLWidget
{
	Q_OBJECT
public:
	LidarViewWidget(LidarViewWidget* parent = nullptr);
	~LidarViewWidget();
protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	void initShaders();
	void initBuffer();

	void mouseMoveEvent(QMouseEvent* event);
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);

	void pollEvents();

private:
	bool firstMouse = true;
	float lastX;
	float lastY;
	QMatrix4x4 m_projectionMatrix;
	Shader* shader;
	VertexBuffer vbo;
	VertexAttribBuffer vao;
	Camera* camera;
	LasParser parser;
	QMatrix4x4 m_modelMatrix;
	bool keys[1024] = { false };
	float deltaTime = 1 / 60.0f;
	QVector<Point> points;

};

