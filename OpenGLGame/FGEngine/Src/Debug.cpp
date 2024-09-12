/**
* @file Debug.cpp
*/
#include "FGEngine/Debug.h"
#include <stdio.h>
#include <stdarg.h>

#pragma warning(push)
#pragma warning(disable:4005)
#include <Windows.h>
#pragma warning(pop)

#include "FGEngine/Package/Glad.h"
#include <string>
#include <fstream>
#include <filesystem>

namespace Debug
{

	/**
	* �����t����������f�o�b�O�E�B���h�E�ɕ\������
	*/
	void Log(Type type, const char* func, const char* format, ...)
	{
		char buffer[1050] = {""};
		char* p = buffer;
		size_t size = sizeof(buffer) - 1;	// ������\n��ǉ������邽��

		// ���O�̎�ނƊ֐�����ݒ�
		static const  char* const typeNames[] = { "�G���[", "�x��", "���" };
		size_t n = snprintf(p, size, "[%s] %s:", typeNames[static_cast<int>(type)], func);
		p += n;
		size -= n;

		// ���b�Z�[�W��ݒ�
		va_list ap;
		va_start(ap, format);
		p += vsnprintf(p, size, format, ap);
		va_end(ap);

		// �����ɉ��s��ǉ�
		p[0] = '\n';
		p[1] = '\0';

		// �쐬������������f�o�b�O�E�B���h�E�ɕ\��
		OutputDebugString(buffer);
	}

	/**
	* OpenGL����̃��b�Z�[�W����������R�[���o�b�N�֐�
	*
	* @param source		���b�Z�[�W�̔��M��
	* @param type		���b�Z�[�W�̎��
	* @param id			���b�Z�[�W����ʂɑI�ʂ���l
	* @param severiry	���b�Z�[�W�̏d�v�x(���A���A���A�Œ�)
	* @param length		���b�Z�[�W�̕������A�����Ȃ烁�b�Z�[�W��0�I�[����Ă���
	* @param message	���b�Z�[�W�{��
	* @param userParam	�R�[���o�b�N�ݒ莞�Ɏw�肵���|�C���^
	*/
	void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		std::string s;
		if (length < 0)
		{
			s = message;
		}
		else
		{
			s.assign(message, message + length);
		}
		s += '\n';
		LOG(s.c_str());
	}

	/**
	* OpenGL����̃f�o�b�O������
	*/
	void OpenGLDebug()
	{
		// ���b�Z�[�W�R�[���o�b�N�ݒ�
		glDebugMessageCallback(DebugCallback, nullptr);
	}
}
