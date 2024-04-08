/**
* @file WindowManager.cpp
*/
#include "WindowManager.h"

namespace FGEngine::WindowSystem
{
	/**
	* �E�B���h�E���쐬
	*
	* @param windowTitle �E�B���h�E�^�C�g��
	*
	* @retval	�쐬�����E�B���h�E�I�u�W�F�N�g
	*			nullptr �쐬�Ɏ��s
	*/
	void WindowManager::CreateWindow(const std::string& windowTitle)
	{
		// �f�o�b�O�R���e�L�X�g�̍쐬
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		// �E�B���h�E���t���X�N���[���ɐݒ�
		//glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

		// �`��E�B���h�E�̍쐬
		auto window = glfwCreateWindow(1280, 720, windowTitle.c_str(), nullptr, nullptr);

		// �E�B���h�E�z��ɒǉ�
		windows.push_back(window);

	}

	/**
	* �E�B���h�E�̕`����J�n
	*/
	void WindowManager::Begin()
	{
		if (windows.empty())
		{
			return;
		}

		for (auto window : windows)
		{
			// �`���̃E�B���h�E��ݒ�
			glfwMakeContextCurrent(window);

			// �o�b�N�o�b�t�@���N���A
			glClearColor(bufferColor.r, bufferColor.g, bufferColor.b, bufferColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

	}

	/**
	* �E�B���h�E�̕`����I��
	*/
	void WindowManager::End()
	{
		size_t i = 0;
		for (auto window : windows)
		{

			// �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�����ւ�
			glfwSwapBuffers(window);

			// OS����̗v������������
			glfwPollEvents();

			// �E�B���h�E�������ꂽ��
			// �E�B���h�E�ƃE�B���h�E�I�u�W�F�N�g���폜����
			if (IsClose(i))
			{
				glfwDestroyWindow(window);
			}

			// �`���E�B���h�E�̐ݒ������
			glfwMakeContextCurrent(nullptr);
			i++;
		}

	}

	/**
	* �E�B���h�E�����Ă��邩�擾
	*
	* @retval true	���Ă���
	* @retval false	���Ă��Ȃ�
	*/
	bool WindowManager::IsClose(size_t index)
	{
		if (!windows[index])
		{
			return true;
		}
		return glfwWindowShouldClose(windows[index]);
	}


	/**
	* �E�B���h�E�I�u�W�F�N�g���擾
	*/
	GLFWwindow& WindowManager::GetWindow(size_t index)
	{
		return *windows[index];
	}

	/**
	* �E�B���h�E�̃T�C�Y��Vector2�Ŏ擾
	*/
	Vector2 WindowManager::GetWindowSize(size_t index)
	{
		// �t���[���o�b�t�@�̑傫�����擾
		int w, h;
		glfwGetFramebufferSize(windows[index], &w, &h);

		return Vector2{ static_cast<float>(w), static_cast<float>(h) };
	}

	/**
	* �E�B���h�E�T�C�Y���擾
	*
	* @param w �E�B���h�E�̉������i�[����
	* @param h �E�B���h�E�̏c�����i�[����
	*/
	void WindowManager::GetWindowSize(GLsizei& w, GLsizei& h, size_t index)
	{
		glfwGetFramebufferSize(windows[index], &w, &h);
	}

	/**
	* �E�B���h�E�̃T�C�Y�̃A�X�y�N�g���擾
	*/
	float WindowManager::GetWindowAspectRatio()
	{
		// �t���[���o�b�t�@�̑傫�����擾
		const Vector2 size = GetWindowSize();

		// �A�X�y�N�g���Ԃ�
		return size.x / size.y;
	}

	/**
	* �o�b�t�@�N���A�̃J���[��ݒ�
	*/
	void WindowManager::SeteBufferClearColor(const Color& color)
	{
		bufferColor = color;
	}
}