/**
* @file WindowManager.cpp
*/
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/Package/Glad.h"
#include "FGEngine/Debug/Debug.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	/**
	* �f�X�g���N�^
	*/
	WindowManager::~WindowManager()
	{
		if (window)
		{
			glfwDestroyWindow(window);
		}
	}

	/**
	* �E�B���h�E�}�l�[�W���[��������
	*
	* @retval true	����������
	* @retval flase	���������s
	*/
	int WindowManager::Initialze()
	{
		// �f�o�b�O�R���e�L�X�g�̍쐬
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		// �E�B���h�E���t���X�N���[���ɐݒ�
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

		// �E�B���h�E�̍쐬
		window = glfwCreateWindow(1280, 720, "Window", nullptr, nullptr);

		if (!window)
		{
			// �E�B���h�E�̍쐬���s
			LOG_ERROR("�E�B���h�E�̍쐬�Ɏ��s���܂���");
			return 1;
		}

		// OpenGL�R���e�L�X�g�̍쐬
		glfwMakeContextCurrent(window);

		// ����������
		return 0;
	}

	/**
	* �E�B���h�E�̕`��J�n
	*/
	void WindowManager::Begin()
	{
		if (!window)
		{
			LOG_WARNINGS("�E�B���h�E������������Ă��܂���");
			return;
		}

		// �`��E�B���h�E���w��
		glfwMakeContextCurrent(window);

		// �o�b�N�o�b�t�@���N���A
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	/**
	* �E�B���h�E�̕`��I��
	*/
	void WindowManager::End()
	{
		if (!window)
		{
			LOG_WARNINGS("�E�B���h�E������������Ă��܂���");
			return;
		}

		// �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�����ւ�
		glfwSwapBuffers(window);

		// OS����̗v������������
		glfwPollEvents();

		// �`���E�B���h�E�̐ݒ������
		glfwMakeContextCurrent(nullptr);
	}

	/**
	* �E�B���h�E�^�C�g�����擾
	*/
	std::string WindowManager::GetTitle() const
	{
		if (!window)
		{
			LOG_WARNINGS("�E�B���h�E������������Ă��܂���");
			return "";
		}

		return glfwGetWindowTitle(window);
	}

	/**
	* �E�B���h�E�^�C�g����ύX
	*
	* @param title �ύX����^�C�g��
	*/
	void WindowManager::SetTitle(const std::string& title)
	{
		if (!window)
		{
			LOG_WARNINGS("�E�B���h�E������������Ă��܂���");
			return;
		}

		glfwSetWindowTitle(window, title.c_str());
	}

	/**
	* �E�B���h�E�̃T�C�Y���擾
	*/
	Vector2 WindowManager::GetSize() const
	{
		if (!window)
		{
			LOG_WARNINGS("�E�B���h�E������������Ă��܂���");
			return Vector2::zero;
		}

		int widht = 0;
		int height = 0;
		// �E�B���h�E�T�C�Y���擾
		glfwGetWindowSize(window, &widht, &height);
		Vector2 size = Vector2(static_cast<float>(widht), static_cast<float>(height));

		return size;
	}

	/**
	* �E�B���h�E�I�u�W�F�N�g���擾
	*/
	GLFWwindow& WindowManager::GetObject() const
	{
		if (!window)
		{
			LOG_WARNINGS("�E�B���h�E������������Ă��܂���");
		}
		return *window;
	}

	/**
	* �E�B���h�E�����Ă��邩�擾
	*
	* @retval true	�E�B���h�E�����Ă���
	* @retval false �E�B���h�E���J���Ă���
	*/
	bool WindowManager::IsClose() const
	{
		if (!window)
		{
			return true;
		}
		return !glfwWindowShouldClose(window);
	}

	/**
	* �E�B���h�E�����
	*/
	void WindowManager::Close()
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}