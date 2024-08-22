/**
* @file BufferAndVAOFrd.h
*/
#ifndef FGENGINE_BUFFERANDVAOFRD_H_INCLUDED
#define FGENGINE_BUFFERANDVAOFRD_H_INCLUDED
#include <memory>

// glad�̐�s�錾
typedef unsigned int GLuint;
typedef int GLint;
typedef unsigned int GLenum;

/**
* BufferAndVAO�̐�s�錾
*/
namespace FGEngine
{
	// �o�b�t�@�I�u�W�F�N�g
	class BufferObject;
	// �o�b�t�@�I�u�W�F�N�g�|�C���^�[
	using BufferObjectPtr = std::shared_ptr<BufferObject>;

	// �t���[���o�b�t�@�I�u�W�F�N�g
	class FrameBufferObject;
	// �t���[���o�b�t�@�I�u�W�F�N�g�|�C���^�[
	using FrameBufferObjectPtr = std::shared_ptr<FrameBufferObject>;

	// �}�b�v�o�b�t�@�I�u�W�F�N�g
	class MappedBufferObject;
	using MappedBufferObjectPtr = std::shared_ptr<MappedBufferObject>;

	// ���_�z��I�u�W�F�N�g
	class VertexArrayObject;
	// ���_�z��I�u�W�F�N�g�|�C���^�[
	using VertexArrayObjectPtr = std::shared_ptr<VertexArrayObject>;
}

#endif // !FGENGINE_BUFFERANDVAOFRD_H_INCLUDED
