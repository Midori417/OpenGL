/**
* @file WindowManager.cpp
*/
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Package/Glad.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	GLFWwindow* WindowManager::window = nullptr;
	Color WindowManager::bufferColor = Color::black;

	/**
	* �E�B���h�E�}�l�[�W���[��������
	*
	* @retval true	����ɏ�����
	* @retval false	���������s
	*/
	bool WindowManager::Initialize()
	{
		// �f�o�b�O�R���e�L�X�g�̍쐬
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		// �E�B���h�E���t���X�N���[���ɐݒ�
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

		// �`��E�B���h�E�̍쐬
		window = glfwCreateWindow(1280, 720, "Window", nullptr, nullptr);
		if (!window)
		{
			return false;
		}

		return true;
	}

	/**
	* �E�B���h�E�̕`����J�n
	*/
	void WindowManager::Begin()
	{
		if (!window)
		{
			return;
		}

		// �`���̃E�B���h�E��ݒ�
		glfwMakeContextCurrent(window);

		// �o�b�N�o�b�t�@���N���A
		glClearColor(bufferColor.r, bufferColor.g, bufferColor.b, bufferColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	/**
	* �E�B���h�E�̕`����I��
	*/
	void WindowManager::End()
	{
		// �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�����ւ�
		glfwSwapBuffers(window);

		// OS����̗v������������
		glfwPollEvents();

		// �E�B���h�E�������ꂽ��
		// �E�B���h�E�ƃE�B���h�E�I�u�W�F�N�g���폜����
		if (IsClose())
		{
			WindowClose();
		}

		// �`���E�B���h�E�̐ݒ������
		glfwMakeContextCurrent(nullptr);
	}

	/**
	* �E�B���h�E�^�C�g�����擾
	*/
	std::string WindowManager::GetTitle()
	{
		if (!window)
		{
			return "";
		}

		return glfwGetWindowTitle(window);
	}

	/**
	* �E�B���h�E�^�C�g����ݒ�
	*
	* @param title �ݒ肷��E�B���h�E�^�C�g��
	*/
	void WindowManager::SetTitle(const std::string& title)
	{
		if (!window)
		{
			return;
		}

		glfwSetWindowTitle(window, title.c_str());
	}

	/**
	* �E�B���h�E�����Ă��邩�擾
	*
	* @retval true	���Ă���
	* @retval false	���Ă��Ȃ�
	*/
	bool WindowManager::IsClose()
	{
		if (!window)
		{
			return true;
		}
		return glfwWindowShouldClose(window);
	}

	/**
	* �E�B���h�E���I��
	*/
	void WindowManager::WindowClose()
	{
		if (!window)
		{
			return;
		}
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}


	/**
	* �E�B���h�E�I�u�W�F�N�g���擾
	*/
	GLFWwindow& WindowManager::GetWindow()
	{
		return *window;
	}

	/**
	* �E�B���h�E�̃T�C�Y��Vector2�Ŏ擾
	*/
	Vector2 WindowManager::GetWindowSize()
	{
		// �t���[���o�b�t�@�̑傫�����擾
		int w, h;
		glfwGetFramebufferSize(window, &w, &h);

		return Vector2{ static_cast<float>(w), static_cast<float>(h) };
	}

	/**
	* �o�b�t�@�N���A�̃J���[��ݒ�
	*/
	void WindowManager::SeteBufferClearColor(const Color& color)
	{
		bufferColor = color;
	}
}