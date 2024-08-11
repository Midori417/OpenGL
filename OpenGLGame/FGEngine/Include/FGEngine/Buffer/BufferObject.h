/**
* @file BufferObject.h
*/
#ifndef FGENGINE_BUFFEROBJECT_H_INCLUDED
#define FGENGINE_BUFFEROBJECT_H_INCLUDED
#include "FGEngine/Package/Glad.h"
#include <memory>

namespace FGEngine
{
	// ��s�錾
	class BufferObject;
	using BufferObjectPtr = std::shared_ptr<BufferObject>;

	/**
	* �o�b�t�@�I�u�W�F�N�g(BO)
	* 
	* GPU�ɃA�N�Z�X���邽�߂̃������̈�
	*/
	class BufferObject
	{
	public:

		/**
		* �R���X�g���N�^
		*
		* @param size	�o�b�t�@�I�u�W�F�N�g�̃o�C�g�T�C�Y
		* @param data	�o�b�t�@�ɃR�s�[����f�[�^�̃A�h���X
		*				nullptr���w�肷��Ƌ�̃o�b�t�@���쐬�����
		* @param flags	�p�r�������r�b�g�t���O�̘_���a(glBufferStorage���Q��)
		*/
		explicit BufferObject(GLsizeiptr size, const void* data = nullptr, GLbitfield flags = 0);

		/**
		* �f�X�g���N�^
		*/
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

		/**
		* �Ǘ��ԍ��̎擾
		*/
		operator GLuint() const;

		/**
		* �o�b�t�@�T�C�Y���擾
		*/
		GLsizeiptr GetSize() const;

	private:

		// �I�u�W�F�N�g�Ǘ��ԍ�
		GLuint id = 0;				

		// �o�b�t�@�T�C�Y(�o�C�g��)
		GLsizeiptr bufferSize = 0;

	};
}
#endif // !BUFFEROBJECT_H_INCLUDED
