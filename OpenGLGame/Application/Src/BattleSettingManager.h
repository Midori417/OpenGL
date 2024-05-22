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

/**
* �o�g���ݒ�}�l�[�W��
*/
class BattleSettingManager : public MonoBehaviour
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

	// �t�F�[�h�R���|�[�l���g
	FadeOutPtr fadeOut;

};

#endif // !BATTLESETTINGMANAGER_H_INCLUDED
