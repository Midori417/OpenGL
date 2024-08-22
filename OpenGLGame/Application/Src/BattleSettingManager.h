/**
* @file BattleSettingManager.h
*/
#ifndef BATTLESETTINGMANAGER_H_INCLUDED
#define BATTLESETTINGMANAGER_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

// ��s�錾
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;
struct BattleInfo;
using BattleInfoPtr = std::shared_ptr<BattleInfo>;

/**
* �o�g���ݒ�}�l�[�W��
*/
class BattleSettingManager : public GameEvent
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	BattleSettingManager() = default;
	virtual ~BattleSettingManager() = default;

private:

	/**
	* �������Ɏ��s
	*/
	virtual void Awake() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

private:

	/**
	* �I������
	*/
	enum class Select
	{
		// �o�g���J�n
		BattleStart,

		// �߂�
		Back,
	};
	Select select = Select::BattleStart;

	// �o�g�����
	BattleInfoPtr battleInfo;

	// �t�F�[�h�R���|�[�l���g
	FadeOutPtr fadeOut;

};

#endif // !BATTLESETTINGMANAGER_H_INCLUDED
