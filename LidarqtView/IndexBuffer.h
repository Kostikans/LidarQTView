#pragma once

#include <GL/glew.h>

class IndexBuffer
{
private:
	GLuint ID;
	GLsizei m_size;
public:
	IndexBuffer() = default;
	IndexBuffer(const unsigned int* m_data, GLsizei size);
	void allocate(const void* m_data, GLsizei size) noexcept;
	GLsizei size() const noexcept;
	void bind() const noexcept;
	void unbind() const noexcept;
};