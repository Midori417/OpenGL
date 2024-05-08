/**
* @file MapBufferObject.h
*/
#ifndef FGENGINE_MAPBUFFEROBJECT_H_INCLUDED
#define FGENGINE_MAPBUFFEROBJECT_H_INCLUDED
#include "Package/Glad.h"
#include <memory>

namespace FGEngine::RenderingSystem
{
	// ��s�錾
	class MappedBufferObject;
	using MappedBufferObjectPtr = std::shared_ptr<MappedBufferObject>;

	/**
	* �o�b�t�@�I�u�W�F�N�g(�}�b�v����)
	*/
	class MappedBufferObject
	{
	public:

		/**
		* �o�b�t�@�I�u�W�F�N�g���쐬����
		*
		* @parma size		�o�b�t�@�I�u�W�F�N�g�̃o�C�g�T�C�Y
		* @param type		�o�b�t�@�I�u�W�F�N�g�̎��
		* @param access		�ȉ��̂����ꂩ���w�肷��
		*					GL_READ_WRITE �ǂݎ�菑�����݂̗��Ή��Ń}�b�v����
		*					GL_READ_ONLY�@�ǂ݂Ƃ��p�Ƃ��ă}�b�v����
		*					GL_WRITE_ONLY �������ݐ�p�Ƃ��ă}�b�v����
		*/
		MappedBufferObject(GLsizeiptr size, GLenum type, GLenum access);

		/**
		* �f�X�g���N�^
		*/
		~MappedBufferObject();

		// �R�s�[�Ƒ�����֎~
		MappedBufferObject(const MappedBufferObject&) = delete;
		MappedBufferObject& operator=(const MappedBufferObject&) = delete;

		/**
		* �o�b�t�@�I�u�W�F�N�g���쐬����
		*
		* @parma size		�o�b�t�@�I�u�W�F�N�g�̃o�C�g�T�C�Y
		* @param type		�o�b�t�@�I�u�W�F�N�g�̎��
		* @param access		�ȉ��̂����ꂩ���w�肷��
		*					GL_READ_WRITE �ǂݎ�菑�����݂̗��Ή��Ń}�b�v����
		*					GL_READ_ONLY�@�ǂ݂Ƃ��p�Ƃ��ă}�b�v����
		*					GL_WRITE_ONLY �������ݐ�p�Ƃ��ă}�b�v����
		*
		* @return �쐬�����o�b�t�@�I�u�W�F�N�g�ւ̃|�C���^
		*/
		static MappedBufferObjectPtr Create(GLsizeiptr size, GLenum type, GLenum access);

		/**
		* �Ǘ��ԍ����擾
		*/
		operator GLuint() const;

		/**
		* �o�b�t�@�T�C�Y���擾
		*/
		GLsizeiptr GetSize() const;

		/**
		* GPU���o�b�t�@���g���I���̂�҂�
		*/
		void WaitSync();

		/**
		* �f�[�^�̃R�s�[��A�h���X���擾����
		*/
		uint8_t* GetMappedAddress()const;

		/**
		* �w�肵���͈͂�OpenGL�R���e�L�X�g�Ɋ��蓖�Ă�
		*
		* @parma index	���蓖�Ă�o�C���f�B���O�|�C���g�ԍ�
		* @param offset	���蓖�Ĕ͈͂̐擪�ʒu
		* @parma size	���蓖�Ĕ͈͂̃o�C�g�T�C�Y
		*/
		void Bind(GLuint index, size_t offset, size_t size);

		/**
		* �R�s�[��o�b�t�@��؂�ւ���
		*/
		void SwapBuffers();

	private:

		// �Ǘ�Id
		GLuint id = 0;

		// �o�b�t�@�T�C�Y
		GLsizeiptr bufferSize = 0;

		// �f�[�^�R�s�[��A�h���X
		uint8_t* p = nullptr;

		// �R�s�[��o�b�t�@�̃C���f�b�N�X
		size_t bufferIndex = 0;		

		// �����I�u�W�F�N�g
		GLsync syncList[2] = { 0, 0};

		// �o�b�t�@�̎��
		GLenum type = GL_ARRAY_BUFFER;	

	};
}
#endif // !MAPBUFFEROBJECT_H_INCLUDED
