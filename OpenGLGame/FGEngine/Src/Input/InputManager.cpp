/**
* @file InputManager.cpp
*/
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Input/InputMouse.h"
#include <GLFW/glfw3.h>

namespace FGEngine::InputSystem
{
	// �X�^�e�B�b�N�ϐ��̏�����
	std::unordered_map<Axis, float> InputManager::axisList;

	/**
	* �C���v�b�g�}�l�[�W����������
	*/
	int InputManager::Initialize()
	{
		// Axis�̒ǉ�
		axisList.emplace(Axis::Horizontal, 0.0f);
		axisList.emplace(Axis::Vertical, 0.0f);

		return 0;
	}

	/**
	* �C���v�b�g�}�l�[�W�����X�V
	* 
	* @param window �E�B���h�E�I�u�W�F�N�g
	*/
	void InputManager::Update(GLFWwindow* window)
	{
		// �L�[�{�[�h�̍X�V
		InputKey::Update(window);

		// �}�E�X���X�V
		InputMouse::Update(window);

		// �A�N�V�Y�̍X�V
		AxisUpdate();
	}

	/**
	* Axis�̍X�V
	*/
	void InputManager::AxisUpdate()
	{
		// Horizontal
		{
			auto horizontal = axisList.find(Axis::Horizontal);
			if (horizontal != axisList.end())
			{
				if (InputKey::GetKey(KeyCode::A) || InputKey::GetKey(KeyCode::LeftArrow))
				{
					horizontal->second = -1;
				}
				else if (InputKey::GetKey(KeyCode::D) || InputKey::GetKey(KeyCode::RightArrow))
				{
					horizontal->second = 1;
				}
				else if (!InputKey::GetKey(KeyCode::A) && !InputKey::GetKey(KeyCode::LeftArrow) &&
					!InputKey::GetKey(KeyCode::D) && !InputKey::GetKey(KeyCode::RightArrow))
				{
					horizontal->second = 0;
				}
			}
		}
		// Vertical
		{
			auto vertical = axisList.find(Axis::Vertical);
			if (vertical != axisList.end())
			{
				if (InputKey::GetKey(KeyCode::S) || InputKey::GetKey(KeyCode::DownArrow))
				{
					vertical->second = -1;
				}
				else if (InputKey::GetKey(KeyCode::W) || InputKey::GetKey(KeyCode::UpArrow))
				{
					vertical->second = 1;
				}
				else if(!InputKey::GetKey(KeyCode::S) && !InputKey::GetKey(KeyCode::DownArrow) && 
					!InputKey::GetKey(KeyCode::W) && !InputKey::GetKey(KeyCode::UpArrow))
				{
					vertical->second = 0;
				}
			}
		}

	}

	/**
	* Axis���擾
	* 
	* @param axis �A�N�V�Y��
	*/
	float InputManager::GetAxis(Axis axis)
	{
		// axis������
		auto tmp = axisList.find(axis);
		if (tmp == axisList.end())
		{
			// �A�N�V�Y���Ή����Ă��Ȃ�
			return 0.0f;
		}

		return tmp->second;
	}
}