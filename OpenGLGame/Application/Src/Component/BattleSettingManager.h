/**
* @file BattleSettingManager.h
*/
#ifndef BATTLESETTINGMANAGER_H_INCLUDED
#define BATTLESETTINGMANAGER_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

// ��s�錾
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;

/**
* �o�g���ݒ�V�[���Ǘ��R���|�[�l���g
*/
class BattleSettingManager : public GameEvent
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BattleSettingManager() = default;

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
	* �I������
	*/
	enum Select
	{
		// �o�g���J�n
		BattleStart,

		// �ݒ�V�[���ɖ߂�
		Espace,
	};
	Select select = Select::BattleStart;

	// �V�[���؂�ւ����̃t�F�[�h�A�E�g�R���|�[�l���g
	FadeOutPtr fadeOut = nullptr;

	// ���艹��炷���߂̃R���|�[�l���g
	AudioSourcePtr audioSource = nullptr;
};

#endif // !BATTLESETTINGMANAGE_H_INCLUDED
