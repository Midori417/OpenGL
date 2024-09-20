/**
* @file HumanPilot.h
*/
#ifndef HYUMANPILOT_H_INCLUDED
#define HYUMANPILOT_H_INCLUDED
#include "BasePilot.h"
#include "FGEngine/Asset/Texture.h"

/**
* �l�ԃp�C���b�g
*/
class HumanPilot : public BasePilot
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	HumanPilot() = default;

private:	// �C�x���g

	/**
	* �ŏ��Ɏ��s
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
	* �Q�[�����͂��X�V
	*/
	void GameInputUpdate();

};
#endif // !HYUMANPILOT_H_INCLUDED