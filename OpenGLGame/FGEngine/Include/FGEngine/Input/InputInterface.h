/**
* @file InputInterface.h
*/
#ifndef FGENGINE_INPUTINTERFACE_H_INCLUDED
#define FGENGINE_INPUTINTERFACE_H_INCLUDED
#include <memory>

// ��s�錾
struct GLFWwindow;

namespace FGEngine
{
	// ��s�錾
	class InputManager;

	/**
	* ���̓f�o�C�X�̃C���^�[�t�F�C�X
	* ���̃N���X�����̉����Ȃ����߃R���X�g���N�^��protected
	*/
	class InputInterface
	{
		friend InputManager;
	protected:

		/**
		* �f�t�H���g�f�X�g���N�^
		*/
		InputInterface() = default;

		/**
		* �f�t�H���g�f�X�g���N�^
		*/
		virtual ~InputInterface() = default;

	protected:

		/**
		* ���͂̏�����
		* 
		* @retval 0		����ɏ�����
		* @retval 0�ȊO	�G���[����
		*/
		virtual int Initialize() = 0;

		/**
		* ���͏�Ԃ̍X�V
		*/
		virtual void Update(GLFWwindow* window) = 0;
	};
	using InputInterfacePtr = std::shared_ptr<InputInterface>;
}

#endif // !FGENGINE_INPUTINTERFACE_H_INCLUDED
