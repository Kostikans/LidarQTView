#pragma once

#include <GL/glew.h>

class VertexBuffer
{
private:
	GLuint ID;

public:
	VertexBuffer() = default;
	void create();
	void allocate(const void* m_data, GLsizei size) noexcept;
	void bind() const noexcept;
	void unbind() const noexcept;
};