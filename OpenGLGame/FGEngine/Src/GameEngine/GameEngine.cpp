/**
* @file GameEngine.cpp
*/
#include "FGEngine/GameEngine/GameEngine.h"
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Debug/Debug.h"

#include "FGEngine/Package/Glad.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{

	/**
	* �Q�[���G���W���ғ�
	*
	* @retval 0		����ɉғ�
	* @retval 0�ȊO	�G���[����
	*/
	int GameEngine::Run()
	{
		if (Initialize() != 0)
		{
			LOG_ERROR("�Q�[���G���W���̏��������s");
			return 1;
		}

		while (isPowerOff)
		{
			if (Update() != 0)
			{
				LOG_ERROR("�Q�[���G���W���̍X�V���ɃG���[����");
				isPowerOff = true;
			}
			Render();
		}

		Finalze();

		return 0;
	}

	/**
	* �Q�[���G���W����������
	*
	* @retval 0		����ɏ�����
	* @retval 0�ȊO	�G���[����
	*/
	int GameEngine::Initialize()
	{	
		// GLFW�̏�����
		if (glfwInit() != GLFW_TRUE)
		{
			LOG_ERROR("GLFW�̏������Ɏ��s");
			return 1;
		}

		// === �G���W���ƃ}�l�[�W���[���쐬�Ǝ擾 === //
		inputManager = InputManager::GetInstance();
		windowManger = WindowManager::GetInstance();

		// OpenGL�̊֐��A�h���X���擾����ɂ̓E�B���h�E���K�v�Ȃ̂łŐ�ɃE�B���h�E�}�l�[�W���[������������
		if (windowManger->Initialze() != 0)
		{
			LOG_ERROR("�E�B���h�E�}�l�[�W���[�̏������Ɏ��s");
			return 1;
		}

		// OpenGL�֐��̃A�h���X���擾
		// OpenGLVersion 4.5
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			LOG_ERROR("OpenGL�̊֐��A�h���X�̎擾�Ɏ��s");
			glfwTerminate();
			return 1;	// �A�h���X�̎擾���s
		}

		Debug::OpenGLSetDebugCall();

		// �G���W���ƃ}�l�[�W���[�������� === //
		if (inputManager->Initialize() != 0)
		{
			LOG_ERROR("���̓}�l�[�W���[�̏������Ɏ��s");
			glfwTerminate();
			return 1;
		}

		return 0;
	}
	int GameEngine::Update()
	{
		return 0;
	}
	void GameEngine::Render()
	{
	}
	void GameEngine::Finalze()
	{
	}

	/**
	* �G���W�����~�߂�
	*/
	void GameEngine::PowerOff()
	{
		isPowerOff = true;
	}
}