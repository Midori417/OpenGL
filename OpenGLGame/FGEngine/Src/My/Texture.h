/**
* @file Texture.h
*/
#ifndef FFGENGINE_TEXTURE_H_INCLUDED
#define FFGENGINE_TEXTURE_H_INCLUDED
#include "Package/Glad.h"
#include "Object.h"

namespace FGEngine
{
	// ��s�錾
	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;

	/**
	* �e�N�X�`���Ǘ��N���X
	*/
	class Texture : public Object
	{
	public:

		// filename�̃e�N�X�`�����쐬����R���X�g���N�^
		explicit Texture(const std::string& name, GLuint object, int width, int height);

		// ��̃e�N�X�`�����쐬����R���X�g���N�^
		explicit Texture(const std::string& name, int width, int height,
			GLenum gpuFormat = GL_RGBA8, GLenum wrapMode = GL_CLAMP_TO_EDGE);

		// �f�X�g���N�^
		~Texture();


		// �R�s�[�Ƒ�����֎~
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

	public:

		/**
		* �e�N�X�`����ǂݍ���ō쐬
		*
		* @param name		�e�N�X�`���̖��O
		* @apram filename	�e�N�X�`���̃t�@�C��
		*
		* @return �쐬�����e�N�X�`���|�C���^�[
		*/
		static std::shared_ptr<Texture> Create(const std::string& name, GLuint object, int width, int height);

		/**
		* ��̃e�N�X�`�����쐬����
		*
		* @param name		�e�N�X�`�����ʗp�̖��O
		* @param widht		�e�N�X�`���̕�(�s�N�Z����)
		* @param height		�e�N�X�`���̍���(�s�N�Z����)
		* @param gpuFormat	�f�[�^�`��
		* @param wrapMode	���b�v���[�h
		*
		* @return �쐬�����e�N�X�`���|�C���^�[
		*/
		static std::shared_ptr<Texture> Create(const std::string& name, int width, int height,
			GLenum gpuFormat = GL_RGBA8, GLenum wrapMode = GL_CLAMP_TO_EDGE);

		/**
		* �e�N�X�`���̊Ǘ��ԍ����擾
		*/
		operator GLuint() const 
		{
			return id;
		}

		/**
		* �����擾
		*/
		int GetWidth() const
		{
			return width;
		}
		/**
		*�������擾
		*/
		int GetHeight() const
		{
			return height;
		}

	private:


		// �e�N�X�`���̊Ǘ��ԍ�
		GLuint id = 0;

		// �e�N�X�`���̕�
		int width = 0;

		// �e�N�X�`���̍���
		int height = 0;

	};
}
#endif // !TEXTURE_H_INCLUDED
