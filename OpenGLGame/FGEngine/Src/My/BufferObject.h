/**
* @file BufferObject.h
*/
#ifndef BUFFEROBJECT_H_INCLUDED
#define BUFFEROBJECT_H_INCLUDED
#include "glad/glad.h"
#include <memory>

// ��s�錾
class BufferObject;
using BufferObjectPtr = std::shared_ptr<BufferObject>;

/**
* �o�b�t�@�I�u�W�F�N�g(BO)
*/
class BufferObject
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	explicit BufferObject(GLsizeiptr size, const void* data = nullptr, GLbitfield flags = 0);
	~BufferObject();

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
	static BufferObjectPtr Create(GLsizeiptr size, const void* data = nullptr, GLbitfield flags = 0);

	// �R�s�[�Ƒ�����֎~
	BufferObject(const BufferObject&) = delete;
	BufferObject& operator=(const BufferObject&) = delete;

	// �Ǘ��ԍ��̎擾
	operator GLuint() const { return id; }

	// �o�b�t�@�T�C�Y���擾
	GLsizeiptr GetSize() const { return bufferSize; }

private:

	GLuint id = 0;				// �I�u�W�F�N�g�Ǘ��ԍ�
	GLsizeiptr bufferSize = 0;	// �o�b�t�@�T�C�Y(�o�C�g��)

};

#endif // !BUFFEROBJECT_H_INCLUDED
