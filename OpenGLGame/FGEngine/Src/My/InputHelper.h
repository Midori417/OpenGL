/**
* @file InputHelper.h
*/
#ifndef INPUTHELPER_H_INCLUDED
#define INPUTHELPER_H_INCLUDED

namespace FGEngine
{
	/// <summary>
	/// �L�[�̏��
	/// </summary>
	struct StKeyState
	{
	public:

		bool old = false;
		bool down = false;
		bool on = false;
		bool up = false;

		float timer = 0;		// �{�^����������Ă��鎞��
		bool push = false;
	};

	/// <summary>
	/// �}�E�X�{�^���̏��
	/// </summary>
	struct MouseButtonState
	{
	public:
		bool old = false;
		bool down = false;
		bool on = false;
		bool up = false;

		bool current = false;	// ���݃t���[���̃{�^���̏��
		bool previous = false;	// �O�t���[���̃{�^���̏��
		bool click = false;		// �N���b�N�̏��
		float timer = 0;		// �{�^����������Ă��鎞��
	};
}
#endif // !INPUTHELPER_H_INCLUDED
