/**
* @file InputMouse.h
*/
#ifndef FGENGINE_INPUTMOUSE_H_INCLUDED
#define FGENGINE_INPUTMOUSE_H_INCLUDED
#include "FGEngine/SystemFrd.h"
#include "MouseButton.h"
#include "FGEngine/Math/Vector2.h"

namespace FGEngine::InputSystem
{
	/**
	* �}�E�X����
	*/
	class InputMouse
	{
	public:

		friend InputSystem::InputManager;
		
		// �R���X�g���N�^�E�f�X�g���N�^
		InputMouse() = default;
		~InputMouse() = default;

	private:

		/**
		* �}�E�X�̏�Ԃ��X�V
		* 
		* @param winndow �E�B���h�E�I�u�W�F�N�g
		*/
		static void Update(GLFWwindow* window);

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

		/**
		* �}�E�X�{�^���̏��
		*/
		struct MouseButtonState
		{
		public:

			// �O��̃t���[���ɉ�����Ă������̗L��
			// true=������Ă��� : false=������Ă��Ȃ�
			bool old = false;

			// �{�^���������������̗L��
			// true=�������� : false=�������Ă��Ȃ�
			bool down = false;
			
			// �{�^�����オ�������̗L��
			// true=�オ���� : false=�オ���Ă��Ȃ�
			bool up = false;
			
			// �{�^����������Ă��邩�̗L��
			// true=������Ă��� : false=������Ă��Ȃ�
			bool on = false;

			// �N���b�N�̗L��
			// true=�N���b�N���� : false=�N���b�N���Ă��Ȃ�
			bool click = false;

			// �{�^����������Ă��鎞��
			float timer = 0;
		};


		// �}�E�X�̏��
		static MouseButtonState mouseButtonsState[(int)MouseButton::Max];

		// �}�E�X�̈ʒu
		static Vector2 mousePosition;

		// �}�E�X�̃N���b�N��t����
		static constexpr float mouseClickSpeed = 0.3f;
	};
}

#endif // !FGENGINE_INPUTMOUSE_H_INCLUDED
