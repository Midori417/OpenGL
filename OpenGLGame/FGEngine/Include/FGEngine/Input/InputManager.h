/**
* @file InputManager.h
*/
#ifndef FGENGINE_INPUTMANAGER_H_INCLUDED
#define FGENGINE_INPUTMANAGER_H_INCLUDED
#include "FGEngine/Singleton.h"
#include "FGEngine/ManagerInterface.h"
#include "InputInterface.h"
#include "KeyCode.h"
#include "MouseButton.h"
#include <unordered_map>

// ��s�錾
struct GLFWwindow;

namespace FGEngine
{
	// ��s�錾
	struct Vector2;
	class InputKey;
	class InputMouse;

	/**
	* �C���v�b�g�}�l�[�W���[
	* ���̓f�o�C�X�Ǘ��N���X
	*/
	class InputManager : public ManagerInterface, public Singleton<InputManager>
	{
		friend Singleton<InputManager>;
	private:

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		InputManager() = default;

	private:

		/**
		* �C���v�b�g�}�l�[�W���[��������
		* 
		* @retval 0		����ɏ�����
		* @retval 0�ȊO	�G���[����
		*/
		virtual int Initialize() override;

		/**
		* �C���v�b�g�}�l�[�W���[�̏�Ԃ��X�V
		*/
		virtual void Update() override;

		/**
		* ���̓f�o�C�X��ǉ�
		* 
		* @param inputDeviec �ǉ�����f�o�C�X
		* 
		* @retval 0		�ǉ�����
		* @retval 0�ȊO	�G���[����
		*/
		int AddDevice(InputInterfacePtr inputDevice);

		/**
		* �L�[�{�[�h�f�o�C�X���擾
		*/
		static std::shared_ptr<InputKey> GetKeyDevice();

		/**
		* �}�E�X�f�o�C�X���擾
		*/
		static std::shared_ptr<InputMouse> GetMouseDevice();

	public:

		/**
		* �L�[��������Ă��邩���擾
		*
		* @param keyCode �Ή����Ă���L�[
		*
		* @retval true	�����Ă���
		* @retval false	�����Ă��Ȃ�
		*/
		static bool GetKey(KeyCode keyCode);

		/**
		* �L�[���オ���������擾
		*
		* @param keyCode �Ή����Ă���L�[
		*
		* @retval true	�����������Ă���
		* @retval false	�����グ���Ă��Ȃ�
		*/
		static bool GetKeyUp(KeyCode keyCode);

		/**
		* �L�[���������������擾
		*
		* @param keyCode �Ή����Ă���L�[
		*
		* @retval true	������������
		* @retval false	�����������Ă��Ȃ�
		*/
		static bool GetKeyDown(KeyCode keyCode);

		/**
		* ��������̃L�[��������Ă��邩�擾
		*
		* @retval true ������Ă���
		* @retval false ������Ă��Ȃ�
		*/
		static bool AnyKey();

	public:

		/**
		* �}�E�X�̈ʒu���擾
		*/
		static Vector2 GetMousePosition();

		/**
		* �}�E�X�̃{�^���������Ă�����擾
		*
		* @param mouseButton �Ή����Ă���{�^��
		*
		* @retval true	�����Ă���
		* @retval false	�����Ă��Ȃ�
		*/
		static bool GetMouseButton(MouseButton mouseButton);

		/**
		* �}�E�X�̃{�^�����オ���������擾
		*
		* @param mouseButton �Ή����Ă���{�^��
		*
		* @retval true	�����������Ă���
		* @retval false	�����グ���Ă��Ȃ�
		*/
		static bool GetMouseButtonUp(MouseButton mouseButton);

		/**
		* �}�E�X�̃{�^�����������������擾
		*
		* @param mouseButton �Ή����Ă���{�^��
		*
		* @retval true	������������
		* @retval false	�����������Ă��Ȃ�
		*/
		static bool GetMouseButtonDown(MouseButton mouseButton);

		/**
		* �}�E�X���N���b�N���������擾
		*
		* @param mouseButton �Ή����Ă���{�^��
		*
		* @retval true �N���b�N����
		* @retval false �N���b�N���Ă��Ȃ�
		*/
		static bool GetMouseButtonClick(MouseButton mouseButton);

	private:

		// �E�B���h�E�I�u�W�F�N�g
		GLFWwindow* window = nullptr;

		// ���̓f�o�C�X�z��
		static std::vector<InputInterfacePtr> inputDevices;
	};
}

#endif // !FGENGINE_INPUTMANAGER_H_INCLUDED
