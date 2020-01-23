#include "VertexAttribBuffer.h"

VertexAttribBuffer::VertexAttribBuffer()
{
}

void VertexAttribBuffer::create()
{
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

void VertexAttribBuffer::pushLayout(const AttribLayout& layout, const VertexBuffer& vbo)
{
	bind();
	vbo.bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		glEnableVertexAttribArray(i);
		offset += element.count * VertexBufferElement::GetSizeofType(element.type);
	}
	// glVertexAttribDivisor(0, 1);
	 //glVertexAttribDivisor(1, 1);
	 //glVertexAttribDivisor(2, 1);

}

void VertexAttribBuffer::bind()
{
	glBindVertexArray(ID);
}

void VertexAttribBuffer::unbind()
{
	glBindVertexArray(0);
}