/**
* @file InputGamePad.h
*/
#ifndef FGENGINE_INPUTGAMEPAD_H_INCLUDED
#define FGENGINE_INPUTGAMEPAD_H_INCLUDED

namespace FGEngine::InputSystem
{
	/**
	* �Q�[���p�p�b�h�̓���
	*/
	class InputGamePad
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		InputGamePad() = default;
		~InputGamePad() = default;

	private:

		/**
		* �Q�[���p�b�h�̏�Ԃ��X�V
		*/
		static void Update();

	private:

	};
}
#endif // !FGENGINE_INPUTGAMEPAD_H_INCOLUDED
