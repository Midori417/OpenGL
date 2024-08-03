/**
* @file InputManager.cpp
*/
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Input/InputMouse.h"
#include "FGEngine/Debug/Debug.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	std::vector<InputInterfacePtr> InputManager::inputDevices;

	/**
	* ���̓f�o�C�X�̎��
	*/
	enum InputDeviceType
	{
		// �L�[�{�[�h
		Key,

		// �}�E�X
		Mouse,
	};

	/**
	* �C���v�b�g�}�l�[�W����������
	* 
	* @retval 0		����ɏ�����
	* @retval 0�ȊO	�G���[����
	*/
	int InputManager::Initialize()
	{
		// �L�[�{�[�h�f�o�C�X��ǉ�
		if(AddDevice(std::make_shared<InputKey>()) != 0)
		{
			LOG_ERROR("�L�[�{�[�h�f�o�C�X�̒ǉ��Ɏ��s");
			return 1;
		}
		// �}�E�X�f�o�C�X��ǉ�
		if (AddDevice(std::make_shared<InputMouse>()) != 0)
		{
			LOG_ERROR("�}�E�X�f�o�C�X�̒ǉ��Ɏ��s");
			return 1;
		}

		// ����������
		return 0;
	}

	/**
	* �C���v�b�g�}�l�[�W�����X�V
	*/
	void InputManager::Update()
	{
		// �f�o�C�X�̏�Ԃ��X�V
		for (auto& x : inputDevices)
		{
			x->Update(window);
		}
	}

	/**
	* ���̓f�o�C�X��ǉ�
	*
	* @param inputDeviec �ǉ�����f�o�C�X
	*
	* @retval 0		�ǉ�����
	* @retval 0�ȊO	�G���[����
	*/
	int InputManager::AddDevice(InputInterfacePtr inputDevice)
	{
		// �f�o�C�X��������
		int result = inputDevice->Initialize();

		if (result != 0)
		{
			// �f�o�C�X�̏������Ɏ��s
			return result;
		}

		// �f�o�C�X��z��ɒǉ�
		inputDevices.push_back(inputDevice);

		return 0;
	}

	/**
	* �L�[�{�[�h�f�o�C�X���擾
	*/
	std::shared_ptr<InputKey> InputManager::GetKeyDevice()
	{
		auto inputKey = std::dynamic_pointer_cast<InputKey>(inputDevices[InputDeviceType::Key]);
		if (!inputKey)
		{
			LOG_ERROR("�L�[�{�[�h�f�o�C�X�����݂��܂���");
			return nullptr;
		}
		return inputKey;
	}

	/**
	* �}�E�X�f�o�C�X���擾
	*/
	std::shared_ptr<InputMouse> InputManager::GetMouseDevice()
	{
		auto inputMouse = std::dynamic_pointer_cast<InputMouse>(inputDevices[InputDeviceType::Mouse]);
		if (!inputMouse)
		{
			LOG_ERROR("�}�E�X�f�o�C�X�����݂��܂���");
			return nullptr;
		}
		return inputMouse;
	}

#pragma region Key

	/**
	* �L�[��������Ă��邩���擾
	*
	* @param keyCode �Ή����Ă���L�[
	*
	* @retval true	�����Ă���
	* @retval false	�����Ă��Ȃ�
	*/
	bool InputManager::GetKey(KeyCode keyCode)
	{
		return GetKeyDevice()->GetKey(keyCode);
	}

	/**
	* �L�[���オ���������擾
	*
	* @param keyCode �Ή����Ă���L�[
	*
	* @retval true	�����������Ă���
	* @retval false	�����グ���Ă��Ȃ�
	*/
	bool InputManager::GetKeyUp(KeyCode keyCode)
	{
		return GetKeyDevice()->GetKeyUp(keyCode);
	}

	/**
	* �L�[���������������擾
	*
	* @param keyCode �Ή����Ă���L�[
	*
	* @retval true	������������
	* @retval false	�����������Ă��Ȃ�
	*/
	bool InputManager::GetKeyDown(KeyCode keyCode)
	{
		return GetKeyDevice()->GetKeyDown(keyCode);
	}

	/**
	* ��������̃L�[��������Ă��邩�擾
	*
	* @retval true ������Ă���
	* @retval false ������Ă��Ȃ�
	*/
	bool InputManager::AnyKey()
	{
		return GetKeyDevice()->AnyKey();
	}

#pragma endregion

#pragma region Mouse

	/**
	* �}�E�X�̈ʒu���擾
	*/
	Vector2 InputManager::GetMousePosition()
	{
		return GetMouseDevice()->GetMousePosition();
	}

	/**
	* �}�E�X�̃{�^���������Ă�����擾
	*
	* @param mouseButton �Ή����Ă���{�^��
	*
	* @retval true	�����Ă���
	* @retval false	�����Ă��Ȃ�
	*/
	bool InputManager::GetMouseButton(MouseButton mouseButton)
	{
		return GetMouseDevice()->GetMouseButton(mouseButton);
	}

	/**
	* �}�E�X�̃{�^�����オ���������擾
	*
	* @param mouseButton �Ή����Ă���{�^��
	*
	* @retval true	�����������Ă���
	* @retval false	�����グ���Ă��Ȃ�
	*/
	bool InputManager::GetMouseButtonUp(MouseButton mouseButton)
	{
		return GetMouseDevice()->GetMouseButtonUp(mouseButton);
	}

	/**
	* �}�E�X�̃{�^�����������������擾
	*
	* @param mouseButton �Ή����Ă���{�^��
	*
	* @retval true	������������
	* @retval false	�����������Ă��Ȃ�
	*/
	bool InputManager::GetMouseButtonDown(MouseButton mouseButton)
	{
		return GetMouseDevice()->GetMouseButtonDown(mouseButton);
	}

	/**
	* �}�E�X���N���b�N���������擾
	*
	* @param mouseButton �Ή����Ă���{�^��
	*
	* @retval true �N���b�N����
	* @retval false �N���b�N���Ă��Ȃ�
	*/
	bool InputManager::GetMouseButtonClick(MouseButton mouseButton)
	{
		return GetMouseDevice()->GetMouseButtonClick(mouseButton);
	}

#pragma endregion
}