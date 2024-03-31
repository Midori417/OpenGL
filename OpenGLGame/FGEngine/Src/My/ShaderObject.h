/**
* @file ShaderObject.h
*/
#ifndef FGENGINE_SHADEROBJECT_H_INCLUDED
#define FGENGINE_SHADEROBJECT_H_INCLUDED
#include "Package/Glad.h"
#include "Object.h"
#include <string>
#include <memory>

namespace FGEngine
{
	// ��s�錾
	class ShaderObject;
	using ShaderObjectPtr = std::shared_ptr<ShaderObject>;

	/**
	* �V�F�[�_�I�u�W�F�N�g
	*/
	class  ShaderObject : public Object
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		ShaderObject(const std::string& name, const char* filenameVS, const char* filenameFS);
		~ShaderObject();

		// �R�s�[�Ƒ�����֎~
		ShaderObject(const ShaderObject&) = delete;
		ShaderObject& operator=(const ShaderObject&) = delete;

		/*
		* �V�F�[�_�I�u�W�F�N�g���쐬
		* 
		* @param name �V�F�[�_�̖��O
		* @param filenameVS	�o�[�e�b�N�X�V�F�[�_�̃t�@�C��
		* @param filenameFS �t���O�����g�V�F�[�_�̃t�@�C��
		* 
		* @return �쐬�����V�F�[�_�I�u�W�F�N�g
		*/
		std::shared_ptr<ShaderObject> Create(const std::string& name, const char* filenameVS, const char* filenameFS);

		/**
		* �v���O�����I�u�W�F�N�g�Ǘ��ԍ����擾
		*/
		operator GLuint() const
		{
			return prog;
		}


	private:

		// ���_�V�F�[�_�Ǘ��ԍ�
		GLuint vs = 0;

		// �t���O�����g�V�F�[�_�Ǘ��ԍ�
		GLuint fs = 0;

		// �v���O�����I�u�W�F�N�g�Ǘ��ԍ�
		GLuint prog = 0;
	};
}
#endif // !PROGRRAMOBJECT_H_INCLUDED
