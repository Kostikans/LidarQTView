#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* m_data, GLsizei size)
{
	m_size = size;
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, m_data, GL_DYNAMIC_DRAW);
}

void IndexBuffer::allocate(const void* m_data, GLsizei size) noexcept
{
	m_size = size;
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, m_data, GL_DYNAMIC_DRAW);
}

GLsizei IndexBuffer::size() const noexcept
{
	return m_size;
}

void IndexBuffer::bind() const noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::unbind() const noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}