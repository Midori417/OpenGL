/**
* @file InputKey.h
*/
#ifndef FGENGINE_INPUTKEY_H_INCLUDED
#define FGENGINE_INPUTKEY_H_INCLUDED
#include "InputInterface.h"
#include <vector>

namespace FGEngine
{
	// ��s�錾
	enum class KeyCode;

	/**
	* �L�[�{�[�h����
	*/
	class InputKey : public InputInterface
	{
	public:

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		InputKey() = default;

	private:

		/**
		* �L�[���͂�������
		* 
		* @retval 0		����������
		* @retval 0�ȊO	���������s
		*/
		virtual int Initialize() override;

		/**
		* �L�[�{�[�h�̏�Ԃ��X�V
		*
		* @param window �E�B���h�E�I�u�W�F�N�g
		*/
		virtual void Update(GLFWwindow* window) override;

	public:

		/**
		* �L�[��������Ă��邩���擾
		*
		* @param keyCode �Ή����Ă���L�[
		*
		* @retval true	�����Ă���
		* @retval false	�����Ă��Ȃ�
		*/
		bool GetKey(KeyCode keyCode) const;

		/**
		* �L�[���オ���������擾
		*
		* @param keyCode �Ή����Ă���L�[
		*
		* @retval true	�����������Ă���
		* @retval false	�����グ���Ă��Ȃ�
		*/
		bool GetKeyUp(KeyCode keyCode) const;

		/**
		* �L�[���������������擾
		*
		* @param keyCode �Ή����Ă���L�[
		*
		* @retval true	������������
		* @retval false	�����������Ă��Ȃ�
		*/
		bool GetKeyDown(KeyCode keyCode) const;

		/**
		* ��������̃L�[��������Ă��邩�擾
		* 
		* @retval true ������Ă���
		* @retval false ������Ă��Ȃ�
		*/
		bool AnyKey() const;

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
		std::vector<KeyState> keyState;

		// ��������̃L�[��������Ă�����true:����������Ă��Ȃ����fasle
		bool isAnyKey = false;
	};
}

#endif // !FGENGINE_INPUTKEY_H_INCLUDED
