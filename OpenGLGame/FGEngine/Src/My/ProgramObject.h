/**
* @file ProgramObject.h
*/
#ifndef PROGRAMOBJECT_H_INCLUDED
#define PROGRAMOBJECT_H_INCLUDED
#include "Package/Glad.h"
#include <string>
#include <memory>

namespace FGEngine
{
	// ��s�錾
	class ProgramObject;
	using ProgramObjectPtr = std::shared_ptr<ProgramObject>;

	/**
	* �v���O�����E�I�u�W�F�N�g���Ǘ�����N���X
	*/
	class  ProgramObject
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		ProgramObject(const std::string& name, const char* filenameVS, const char* filenameFS);
		~ProgramObject();

		// �R�s�[�Ƒ�����֎~
		ProgramObject(const ProgramObject&) = delete;
		ProgramObject& operator=(const ProgramObject&) = delete;

		/*
		* �v���O�����I�u�W�F�N�g���쐬
		*/
		std::shared_ptr<ProgramObject> Create(const std::string& name, const char* filenameVS, const char* filenameFS);

		// �Ǘ��ԍ����擾
		operator GLuint() const
		{
			return prog;
		}


	private:

		std::string name = "Shader";	// �V�F�[�_�[�̖��O
		GLuint vs = 0;			// ���_�V�F�[�_�[
		GLuint fs = 0;			// �t���O�����g�V�F�[�_�[
		GLuint prog = 0;		// �v���O�����I�u�W�F�N�g
		std::string filenameVS;	// ���_�V�F�[�_�[�t�@�C����
		std::string filenameFS;	// �t���O�����g�V�F�[�_�[�t�@�C����
	};
}
#endif // !PROGRRAMOBJECT_H_INCLUDED
