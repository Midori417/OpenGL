/**
* @file InputMouse.h
*/
#ifndef FGENGINE_INPUTMOUSE_H_INCLUDED
#define FGENGINE_INPUTMOUSE_H_INCLUDED
#include "InputInterface.h"
#include "FGEngine/Math/Vector2.h"
#include <vector>

namespace FGEngine
{
	// ��s�錾
	enum class MouseButton;

	/**
	* �}�E�X����
	*/
	class InputMouse : public InputInterface
	{
	public:
		
		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		InputMouse() = default;

	private:

		/**
		* �}�E�X���͂�������
		* 
		* @retval 0		����ɏ�����
		* @retval 0�ȊO	�G���[����
		*/
		virtual int Initialize() override;

		/**
		* �}�E�X�̏�Ԃ��X�V
		*
		* @param winndow �E�B���h�E�I�u�W�F�N�g
		*/
		virtual void Update(GLFWwindow* window) override;

	public:

		/**
		* �}�E�X�̈ʒu���擾
		*/
		Vector2 GetMousePosition();

		/**
		* �}�E�X�̃{�^���������Ă�����擾
		* 
		* @param mouseButton �Ή����Ă���{�^��
		* 
		* @retval true	�����Ă���
		* @retval false	�����Ă��Ȃ�
		*/
		bool GetMouseButton(MouseButton mouseButton);

		/**
		* �}�E�X�̃{�^�����オ���������擾
		* 
		* @param mouseButton �Ή����Ă���{�^��
		* 
		* @retval true	�����������Ă���
		* @retval false	�����グ���Ă��Ȃ�
		*/
		bool GetMouseButtonUp(MouseButton mouseButton);

		/**
		* �}�E�X�̃{�^�����������������擾
		* 
		* @param mouseButton �Ή����Ă���{�^��
		* 
		* @retval true	������������
		* @retval false	�����������Ă��Ȃ�
		*/
		bool GetMouseButtonDown(MouseButton mouseButton);

		/**
		* �}�E�X���N���b�N���������擾
		* 
		* @param mouseButton �Ή����Ă���{�^��
		* 
		* @retval true �N���b�N����
		* @retval false �N���b�N���Ă��Ȃ�
		*/
		bool GetMouseButtonClick(MouseButton mouseButton);

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
		std::vector<MouseButtonState> mouseButtonsState;

		// �}�E�X�̈ʒu
		Vector2 mousePosition = Vector2::zero;

		// �}�E�X�̃N���b�N��t����
		const float mouseClickSpeed = 0.3f;
	};
}

#endif // !FGENGINE_INPUTMOUSE_H_INCLUDED
