/**
* @file ShaderObject.cpp
*/
#include "ShaderObject.h"
#include "Debug.h"
#include <fstream>
#include <filesystem>

namespace FGEngine
{
	/**
	* �V�F�[�_�t�@�C����ǂݍ���ŃR���p�C������
	*
	* @param type		�V�F�[�_�̎��
	* @param filename	�V�F�[�_�t�@�C����
	*
	* @return	�V�F�[�_�̊Ǘ��ԍ�
	*/
	GLuint CompileShader(GLenum type, const char* filename)
	{
		std::ifstream file(filename, std::ios::binary); // �t�@�C�����J��
		if (!file)
		{
			LOG_ERROR("%s���J���܂���", filename);
			return 0;
		}

		// �t�@�C����ǂݍ���
		const size_t filesize = std::filesystem::file_size(filename);
		std::vector<char> buffer(filesize);
		file.read(buffer.data(), filesize);
		file.close();

		// �\�[�X�R�[�h��ݒ肵�ăR���p�C��
		const char* source[] = {
			buffer.data()
		};
		const GLint	length[] = {
			int(buffer.size())
		};
		const GLuint object = glCreateShader(type);
		glShaderSource(object, 1, source, length);
		glCompileShader(object);

		// �R���p�C�����ʂ��`�F�b�N
		GLint status = 0;	// ���ʂ��i�[���錏��

		// �R���p�C�����ʂ��擾
		glGetShaderiv(object, GL_COMPILE_STATUS, &status);

		if (status != GL_TRUE)
		{
			LOG_ERROR("�V�F�[�_�[�̃R���p�C���Ɏ��s(%s)", filename);
			glDeleteShader(object);
			return 0;		// �R���p�C���Ɏ��s
		}

		return object;
	}

	/**
	* �R���X�g���N�^
	*
	* @param filenameVS ���_�V�F�[�_�[�̃t�@�C����
	* @param filenameFS �t���O�����g�V�F�[�_�[�̃t�@�C����
	*/
	ShaderObject::ShaderObject(const std::string& name, const std::string& filenameVS, const std::string& filenameFS)
	{
		// �V�F�[�_�̖��O��ݒ�
		SetName(name);

		// �V�F�[�_�[�ǂݍ���ŃR���p�C��
		vs = CompileShader(GL_VERTEX_SHADER, filenameVS.c_str());
		fs = CompileShader(GL_FRAGMENT_SHADER, filenameFS.c_str());

		if (vs == 0 || fs == 0)
		{
			return; // �R���p�C���Ɏ��s
		}

		// ��̃V�F�[�_�[�������N
		prog = glCreateProgram();
		glAttachShader(prog, vs);
		glAttachShader(prog, fs);
		glLinkProgram(prog);

		// �����N���ʂ��`�F�b�N
		GLint status = 0;

		// �����N���ʂ��擾
		glGetProgramiv(prog, GL_LINK_STATUS, &status);

		if (status != GL_TRUE)
		{
			LOG_ERROR("�V�F�[�_�[�̃����N�Ɏ��s(vs=%s, fs=%s)", filenameVS, filenameFS);
			return;		// �V�F�[�_�[�̃����N�Ɏ��s
		}

		LOG("�V�F�[�_�[���쐬(vs=%s, fs=%s)", filenameVS, filenameFS);
	}

	/**
	* �f�X�g���N�^
	*/
	ShaderObject::~ShaderObject()
	{
		glDeleteProgram(prog);
		glDeleteShader(fs);
		glDeleteShader(vs);
	}

	/*
	* �v���O�����I�u�W�F�N�g���쐬
	*/
	ShaderObjectPtr ShaderObject::Create(const std::string& name, const std::string& filenameVS, const std::string& filenameFS)
	{
		return std::make_shared<ShaderObject>(name, filenameVS, filenameVS);
	}
}