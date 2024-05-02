/**
* @file Texture.cpp
*/
#include "Texture.h"
#include <vector>
#include <fstream>
#include <filesystem>

#pragma warning(push)
#pragma warning(disable:4005)
#include <Windows.h>
#pragma warning(pop)

namespace FGEngine
{

	/**
	* �R���X�g���N�^
	*
	* @param filename �e�N�X�`���t�@�C����
	*
	*/
	Texture::Texture(const std::string& name, GLuint object, int width, int height)
		: id(object), width(width), height(height)
	{		
		// ���O��ݒ�
		this->SetName(name);
	}

	/**
	* ��̃e�N�X�`�����쐬����R���X�g���N�^
	*
	* @param name		�e�N�X�`�����ʗp�̖��O
	* @param widht		�e�N�X�`���̕�(�s�N�Z����)
	* @param height		�e�N�X�`���̍���(�s�N�Z����)
	* @param gpuFormat	�f�[�^�`��
	* @param wrapMode	���b�v���[�h
	*/
	Texture::Texture(const std::string& name, int width, int height, GLenum gpuFormat, GLenum wrapMode)
		: width(width), height(height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, gpuFormat, width, height);
		glTextureParameteri(id, GL_TEXTURE_WRAP_S, wrapMode);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, wrapMode);

		// �[�x�e�N�X�`���̏ꍇ�A�V���h�E�}�b�s���O�̂��߂ɔ�r���[�h��ݒ肷��
		switch (gpuFormat)
		{
		case GL_DEPTH_COMPONENT16:
		case GL_DEPTH_COMPONENT24:
		case GL_DEPTH_COMPONENT32:
		case GL_DEPTH_COMPONENT32F:
			glTextureParameteri(id, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
			break;
		default:
			break;
		}
		SetName(name);
	}

	/**
	* �f�X�g���N�^
	*/
	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
	}

	/**
	* �e�N�X�`����ǂݍ���ō쐬
	* 
	* @param name		�e�N�X�`���̖��O
	* @apram filename	�e�N�X�`���̃t�@�C��
	* 
	* @return �쐬�����e�N�X�`���|�C���^�[
	*/
	std::shared_ptr<Texture> Texture::Create(const std::string& name, GLuint object, int width, int height)
	{
		return std::make_shared<Texture>(name, object, width, height);
	}

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
	std::shared_ptr<Texture> Texture::Create(const std::string& name, int width, int height, GLenum gpuFormat, GLenum wrapMode)
	{
		return std::make_shared<Texture>(name, width, height, gpuFormat, wrapMode);
	}
}