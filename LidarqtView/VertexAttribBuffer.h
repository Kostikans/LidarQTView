#pragma once

#include <GL/glew.h>
#include "AttribLayout.h"
#include "VertexBuffer.h"

class VertexAttribBuffer
{
private:
	GLuint ID;

public:
	VertexAttribBuffer();
	void create();
	void pushLayout(const AttribLayout& layout, const VertexBuffer& vbo);
	void bind();
	void unbind();
};