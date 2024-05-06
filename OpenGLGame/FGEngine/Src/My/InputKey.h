/**
* @file InputKey.h
*/
#ifndef FGENGINE_INPUTKEY_H_INCLUDED
#define FGENGINE_INPUTKEY_H_INCLUDED
#include "SystemFrd.h"
#include "KeyCode.h"

namespace FGEngine::InputSystem
{
	/**
	* �L�[�{�[�h����
	*/
	class InputKey
	{
	public:

		friend InputSystem::InputManager;

		// �R���X�g���N�^�E�f�X�g���N�^
		InputKey() = default;
		~InputKey() = default;

	private:

		/**
		* �L�[�{�[�h�̏�Ԃ��X�V
		* 
		* @param window �E�B���h�E�I�u�W�F�N�g
		*/
		static void Update(GLFWwindow* window);

	public:

		/**
		* �L�[��������Ă��邩���擾
		*
		* @param keyCod	�Ή����Ă���L�[
		*
		* @retval true	�����Ă���
		* @retval false	�����Ă��Ȃ�
		*/
		static bool GetKey(KeyCode keyCode);

		/**
		* �L�[���オ���������擾
		*
		* @param keyCod	�Ή����Ă���L�[
		*
		* @retval true	�����������Ă���
		* @retval false	�����グ���Ă��Ȃ�
		*/
		static bool GetKeyUp(KeyCode keyCode);

		/**
		* �L�[���������������擾
		*
		* @param keyCod	�Ή����Ă���L�[
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

	private:

		/**
		* �L�[�̏��
		*/
		struct KeyState
		{
			// �O��̃t���[���ɉ�����Ă������̗L��
			// true=������Ă��� : false=������Ă��Ȃ�
			bool old = false;

			//	�L�[�������������̗L��
			// true=�������� : false=�������Ă��Ȃ�
			bool down = false;

			// �L�[���オ�������̗L��
			// true=�オ���� : false=�オ���Ă��Ȃ�
			bool up = false;

			// �L�[��������Ă��邩�̗L��
			// true=������Ă��� : false=������Ă��Ȃ�
			bool on = false;
		};


		// �L�[�̏�Ԕz��
		static KeyState keyState[(int)KeyCode::Max];

		// ��������̃L�[��������Ă�����true:����������Ă��Ȃ����fasle
		static bool anyKey;
	};
}

#endif // !FGENGINE_INPUTKEY_H_INCLUDED
