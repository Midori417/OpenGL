/**
* @file MapBufferObject.h
*/
#ifndef MAPBUFFEROBJECT_H_INCLUDED
#define MAPBUFFEROBJECT_H_INCLUDED
#include "glad/glad.h"
#include <memory>

class MappedBufferObject;
using MappedBufferObjectPtr = std::shared_ptr<MappedBufferObject>;

/**
* �o�b�t�@�I�u�W�F�N�g(�}�b�v����)
*/
class MappedBufferObject
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	MappedBufferObject(GLsizeiptr size, GLenum type, GLenum access);
	~MappedBufferObject();

	static MappedBufferObjectPtr Create(GLsizeiptr size, GLenum type, GLenum access);

	// �Ǘ��ԍ����擾����
	operator GLuint() const { return id; }
	GLsizeiptr GetSize() const { return bufferSize; }

	void WaitSync();
	uint8_t* GetMappedAddress()const;
	void Bind(GLuint index, size_t offset, size_t size);
	void SwapBuffers();

private:

	GLuint id = 0;
	GLsizeiptr bufferSize = 0;

	uint8_t* p = nullptr;			// �f�[�^�R�s�[��A�h���X
	size_t bufferIndex = 0;			// �R�s�[��o�b�t�@�̃C���f�b�N�X
	GLsync syncList[2] = { 0,0 };	// �����I�u�W�F�N�g
	GLenum type = GL_ARRAY_BUFFER;	// �o�b�t�@�̎��

};

#endif // !MAPBUFFEROBJECT_H_INCLUDED
