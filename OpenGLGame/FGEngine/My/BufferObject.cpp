/**
* @file BufferObject.cpp
*/
#include "BufferObject.h"
#include "Debug.h"

namespace FGEngine::RenderingSystem
{

	/**
	* �R���X�g���N�^
	*
	* @param size	�o�b�t�@�I�u�W�F�N�g�̃o�C�g�T�C�Y
	* @param data	�o�b�t�@�ɃR�s�[����f�[�^�̃A�h���X
	*				nullptr���w�肷��Ƌ�̃o�b�t�@���쐬�����
	* @param flags	�p�r�������r�b�g�t���O�̘_���a(glBufferStorage���Q��)
	*/
	BufferObject::BufferObject(GLsizeiptr size, const void* data, GLbitfield flags)
		:bufferSize(size)
	{
		glCreateBuffers(1, &id);
		glNamedBufferStorage(id, bufferSize, data, flags);
	}

	/**
	* �f�X�g���N�^
	*/
	BufferObject::~BufferObject()
	{
		glDeleteBuffers(1, &id);
	}

	/**
	* �o�b�t�@�I�u�W�F�N�g���쐬����
	*
	* @param size	�o�b�t�@�I�u�W�F�N�g�̃o�C�g�T�C�Y
	* @param data	�o�b�t�@�ɃR�s�[����f�[�^�̃A�h���X
	*				nullptr���w�肷��Ƌ�̃o�b�t�@���쐬�����
	* @param flags	�p�r�������r�b�g�t���O�̘_���a(glBufferStorage���Q��)
	*
	* @return �쐬�����o�b�t�@�I�u�W�F�N�g�̃|�C���^�[
	*/
	BufferObjectPtr BufferObject::Create(GLsizeiptr size, const void* data, GLbitfield flags)
	{
		return std::make_shared<BufferObject>(size, data, flags);
	}

	/**
	* �Ǘ��ԍ����擾
	*/
	BufferObject::operator GLuint() const
	{
		return id;
	}

	/**
	* �o�b�t�@�T�C�Y���擾
	*/
	GLsizeiptr BufferObject::GetSize() const
	{
		return bufferSize;
	}
}