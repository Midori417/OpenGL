/**
* @file Shader.h
*/
#ifndef FGENGINE_SHADER_H_INCLUDED
#define FGENGINE_SHADER_H_INCLUDED
#include "Package/Glad.h"
#include <string>
#include <memory>

namespace FGEngine
{
	// ��s�錾
	class Shader;
	using ShaderPtr = std::shared_ptr<Shader>;

	/**
	* �V�F�[�_�I�u�W�F�N�g
	*/
	class  Shader
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Shader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS);
		~Shader();

		// �R�s�[�Ƒ�����֎~
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		/*
		* �V�F�[�_�I�u�W�F�N�g���쐬
		* 
		* @param name �V�F�[�_�̖��O
		* @param filenameVS	�o�[�e�b�N�X�V�F�[�_�̃t�@�C��
		* @param filenameFS �t���O�����g�V�F�[�_�̃t�@�C��
		* 
		* @return �쐬�����V�F�[�_�I�u�W�F�N�g
		*/
		static ShaderPtr Create(const std::string& name, const std::string& filenameVS, const std::string& filenameFS);

		/**
		* �v���O�����I�u�W�F�N�g�Ǘ��ԍ����擾
		*/
		GLuint GetProgId() const
		{
			return prog;
		}

		/**
		* �V�F�[�_�̖��O���擾
		*/
		std::string ToString() const
		{
			return name;
		}

	public:

		bool isNormal = false;

		bool isShadow = false;

		bool isLight = false;

		bool isUseLight = false;

	private:

		// �V�F�[�_�̖��O
		std::string name;

		// ���_�V�F�[�_�Ǘ��ԍ�
		GLuint vs = 0;

		// �t���O�����g�V�F�[�_�Ǘ��ԍ�
		GLuint fs = 0;

		// �v���O�����I�u�W�F�N�g�Ǘ��ԍ�
		GLuint prog = 0;

	};
}
#endif // !PROGRRAMOBJECT_H_INCLUDED
