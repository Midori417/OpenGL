/**
* @file HyumanControl.h
*/
#ifndef HYUMANCONTROL_H_INCLUDED
#define HYUMANCONTROL_H_INCLUDED
#include "BaseControl.h"

/**
* �l�Ԃ�����
*/
class HyumanControl : public BaseControl
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	HyumanControl() = default;

private:

	/**
	* Update���n�܂�O�Ɉ�x���s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	/**
	* ���ɃN���[������\�肪�Ȃ��̂ŉ��������Ȃ�
	*/
	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

private:

	/**
	* �@�̂̑�����X�V
	*/
	virtual void GameInputUpdate() override;

};

#endif // !HYUMANCONTROL_H_INCLUDED
