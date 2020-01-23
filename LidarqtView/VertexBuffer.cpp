#include "VertexBuffer.h"

void VertexBuffer::create()
{
	glGenBuffers(1, &ID);
}

void VertexBuffer::allocate(const void* m_data, GLsizei size) noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, m_data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind() const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}