/**
* @file InputManager.cpp
*/
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Input/InputMouse.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	std::shared_ptr<InputKey> InputManager::inputKey;
	std::shared_ptr<InputMouse> InputManager::inputMouse;
	std::unordered_map<Axis, float> InputManager::axisList;

	/**
	* �C���v�b�g�}�l�[�W����������
	* 
	* @param window �E�B���h�E�I�u�W�F�N�g
	* 
	* @retval true	����ɏ�����
	* @retval false	���������s
	*/
	bool InputManager::Initialize(GLFWwindow* window)
	{
		this->window = window;

		// ���͂𐶐�
		inputKey = InputKey::GetInstance();
		if (!inputKey)
		{
			return false;
		}
		inputMouse = InputMouse::GetInstance();
		if (!inputMouse)
		{
			return false;
		}

		// ���͂�������
		if (!inputKey->Initialize())
		{
			return false;
		}
		if (!inputMouse->Initialize())
		{
			return false;
		}

		// Axis�̒ǉ�
		axisList.emplace(Axis::Horizontal, 0.0f);
		axisList.emplace(Axis::Vertical, 0.0f);

		return true;
	}

	/**
	* �C���v�b�g�}�l�[�W���[�̏�Ԃ��X�V
	*/
	void InputManager::Update()
	{
		// �E�B���h�E�I�u�W�F�N�g���Ȃ���Ή������Ȃ�
		if (!window)
		{
			return;
		}

		// ���͂��X�V
		inputKey->Update(window);
		inputMouse->Update(window);

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