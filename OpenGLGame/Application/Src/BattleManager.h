/**
* @file BattleManager.h
*/
#ifndef BATTLEMANAGER_H_INCLUDED
#define BATTLEMANAGER_H_INCLUDED
#include "FGEngine.h"
#include "MsLilst.h"
using namespace FGEngine;
using namespace FGEngine::UI;

// ��s�錾
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class ControlOwner;
using ControlOwnerPtr = std::shared_ptr<ControlOwner>;
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;
struct BattleInfo;
using BattleInfoPtr = std::shared_ptr<BattleInfo>;

/**
* �o�g���}�l�[�W��
*/
class BattleManager : public MonoBehaviour

{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	BattleManager() = default;
	virtual ~BattleManager() = default;

	/**
	* �o�g������ݒ�
	*/
	static void SetBattleInfo(BattleInfoPtr _battleInfo);

private:

	/**
	* �������Ɏ��s
	*/
	virtual void Awake() override;

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	/**
	* ms�ɑΉ�����R���|�[�l���g��obj�ɒǉ�����
	*
	* @param obj �ǉ�����I�u�W�F�N�g
	* @param ms �ǉ��������R���|�[�l���g�ɑΉ�����MsList
	*/
	BaseMsPtr SetMs(GameObjectPtr obj,  MsList ms);

private:

	/**
	* �o�g�����
	*/
	enum class GameState
	{
		// ����
		Ready,

		// �ҋ@
		Standbay,

		// �X�^�[�g
		GO,

		// �퓬��
		Battle,

		// ���s
		Victory,
	};
	GameState state = GameState::Ready;

	// �^�C�}�[
	float timer = 0;

	// ��������
	float readyTime = 1.5f;

	// �X�^���o�C����
	const float standbayTime = 2;

	// �S�[�^�C��
	const float goTime = 1;

	// �o�g�����
	static BattleInfoPtr battleInfo;

	// �`�[���P�R���g���[���z��
	std::vector<ControlOwnerPtr> teum1ControlOwners;

	// �`�[��2�R���g���[���z��
	std::vector<ControlOwnerPtr> teum2ControlOwners;
	
	// �`�[��1�̗�
	std::shared_ptr<int> teum1Hp = 0;

	// �`�[��2�̗�
	std::shared_ptr<int> teum2Hp = 0;

	// �o�g���^�C��
	float battleTime = 0;

	// === UI === //

	// �X�^���o�C
	ImagePtr imgStandbay;

	// �S�[
	ImagePtr imgGo;

	// �S�[�̔w�i
	ImagePtr imgGoBack;

	// ����
	ImagePtr imgWin;

	// �s�k
	ImagePtr imgLose;
};


#endif // !BATTLEMANAGER_H_INCLUDED
