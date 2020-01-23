#include "OpenGLWidget.h"
#include <QtCore\qdebug.h>
#include <QtCore\qmath.h>

LidarViewWidget::LidarViewWidget(LidarViewWidget* parent)
	:QOpenGLWidget(parent)
{
	camera = new Camera(QVector3D(0.0f, 0.0f, 4.0f));

	this->setMouseTracking(true);

	lastX = size().width() / 2.0f;
	lastY = size().height() / 2.0f;

	makeCurrent();
}

LidarViewWidget::~LidarViewWidget()
{}


void LidarViewWidget::initializeGL()
{

	glewInit();
	glClearColor(0.00f, 0.05f, 0.05f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	initShaders();
	//points = parser.ReadAndCreate("G://download//Dendro//dendro.las");
	points = parser.Read("C://Users//ea56//source//repos//lidar//lidar//Layers1//5_0layer.las");

	vbo.create();
	vbo.bind();
	vbo.allocate(points.constData(), points.size() * sizeof(Point));

	vao.create();
	AttribLayout layout;
	layout.push<float>(3);
	vao.pushLayout(layout, vbo);


	m_modelMatrix.setToIdentity();

	m_modelMatrix.rotate(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), -90.0f));
}


void LidarViewWidget::resizeGL(int w, int h)
{

	m_projectionMatrix.setToIdentity();
	m_projectionMatrix.perspective(45.0f, w / float(h), 0.01f, 100.0f);
}


void LidarViewWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pollEvents();
	shader->use();
	shader->setMat4("viewMatrix", camera->getViewMatrix());
	shader->setMat4("modelMatrix", m_modelMatrix);
	shader->setMat4("projectionMatrix", m_projectionMatrix);

	//qDebug() << camera->getCameraPos().x() << " " << camera->getCameraPos().y() << " " << camera->getCameraPos().z();
	//qDebug() << keys[Qt::Key::Key_W];
	glPointSize((GLfloat)2.0f);

	vbo.bind();
	glDrawArrays(GL_POINTS, 0, parser.size());
	vbo.unbind();
}


void LidarViewWidget::initShaders()
{
	shader = new Shader("C://Users//ea56//source//repos//lidar//lidar//PointShader.vs", "C://Users//ea56//source//repos//lidar//lidar//PointShader.fs");
}

void LidarViewWidget::initBuffer()
{
}

void LidarViewWidget::mouseMoveEvent(QMouseEvent* event)
{

	if (firstMouse)
	{
		lastX = event->localPos().x();
		lastY = event->localPos().y();
		firstMouse = false;
	}

	float xoffset = event->localPos().x() - lastX;
	float yoffset = lastY - event->localPos().y();

	lastX = event->localPos().x();
	lastY = event->localPos().y();

	if (event->buttons() == Qt::LeftButton)
	{
		camera->ProcessMouseMovement(xoffset, yoffset);
		this->update();
	}
}

void LidarViewWidget::keyPressEvent(QKeyEvent* event)
{
	if (event->type() == QKeyEvent::KeyPress)
	{
		int ikey = event->key();
		keys[ikey] = true;
	}
	this->update();
}

void LidarViewWidget::keyReleaseEvent(QKeyEvent* event)
{
	int ikey = event->key();
	keys[ikey] = false;
	this->update();
}

void LidarViewWidget::pollEvents()
{
	if (keys[Qt::Key::Key_W] == true)
	{
		camera->ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[Qt::Key::Key_S] == true)
	{
		camera->ProcessKeyboard(BACKWARD, deltaTime);

	}


	if (keys[Qt::Key::Key_A] == true)
	{
		camera->ProcessKeyboard(LEFT, deltaTime);

	}


	if (keys[Qt::Key::Key_D] == true)
	{
		camera->ProcessKeyboard(RIGHT, deltaTime);

	}
	this->update();
}

