/**
* @file VertexArrayObject.cpp
*/
#include "FGEngine/BufferAndVAO/VertexArrayObject.h"
#include "FGEngine/Package/Glad.h"

namespace FGEngine
{
	/**
	* �R���X�g���N�^
	*/
	VertexArrayObject::VertexArrayObject()
	{
		glCreateVertexArrays(1, &id);
	}

	/**
	* �f�X�g���N�^
	*/
	VertexArrayObject::~VertexArrayObject()
	{
		glDeleteVertexArrays(1, &id);
	}

	/**
	* VertexArrayObject���쐬
	* 
	* @return �쐬����VertexArrayObject�|�C���^�[
	*/
	VertexArrayObjectPtr VertexArrayObject::Create()
	{
		return std::make_shared<VertexArrayObject>();
	}

	/**
	* GPU��VAO���o�C���h����
	*/
	void VertexArrayObject::Bind()
	{
		glBindVertexArray(id);
	}

	/**
	* ���_�A�g���r���[�g��ݒ�
	*
	* @param index	�ݒ肷�钸�_�A�g���r���[�g�̔ԍ�(0�`15)
	* @param size	�v�f�̃f�[�^��
	* @param stride	���̒��_�f�[�^�ɂ��铯��v�f�܂ł̊��o(�o�C�g��)
	* @param offset ���_�f�[�^���ɂ�����v�f�̈ʒu(�o�C�g��)
	*/
	void VertexArrayObject::SetAttribute(GLuint index, GLint size, size_t stride, size_t offset)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), reinterpret_cast<void*>(offset));
	}
}