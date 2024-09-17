/**
* @file BattleManager.h
*/
#ifndef BATTLEMANAGER_H_INCLUDED
#define BATTLEMANAGER_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

#include "../MsList.h"

// ��s�錾
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class BasePilot;
using BasePilotPtr = std::shared_ptr<BasePilot>;
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;
struct BattleInfo;
using BattleInfoPtr = std::shared_ptr<BattleInfo>;

/**
* �o�g���}�l�[�W��
*/
class BattleManager : public GameEvent
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BattleManager() = default;

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
	* ���ɃN���[������\�肪�Ȃ��̂ŉ��������Ȃ�
	*/
	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

public:

	/**
	* �o�g������ݒ�
	*/
	static void SetBattleInfo(BattleInfoPtr _battleInfo);

	/**
	* ���X�|�[���ʒu
	*/
	void SetResponPos(const std::vector<Vector3>& poses);

private:

	void BattleSetting();

	/**
	* ms�ɑΉ�����R���|�[�l���g��obj�ɒǉ�����
	*
	* @param obj �ǉ�����I�u�W�F�N�g
	* @param ms �ǉ��������R���|�[�l���g�ɑΉ�����MsList
	*/
	BaseMsPtr SetMs(GameObjectPtr obj,  MsList ms);

	/**
	* �`�[����ݒ肷��
	*
	* @param control	�ݒ肷��R���g���[��
	* @param id			�`�[��ID
	*/
	void SetTeum(const BasePilotPtr& control, int id);

private:

	// �o�g�����
	static BattleInfoPtr battleInfo;

	// ���A�ʒu
	// �z�� 0=Team1,1 = Teum2�̏����ʒu
	std::vector<Vector3> responPoses;

private:

	/**
	* �o�g�����
	*/
	enum class BattleState
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
	BattleState battleState = BattleState::Ready;

	// �^�C�}�[
	float timer = 0;

	// ��������
	const float readyTime = 1.5f;

	// �X�^���o�C����
	const float standbayTime = 2;

	// �S�[�^�C��
	const float goTime = 1;

private:

	// �o�g���ɎQ�����Ă���p�C���b�g�z��
	std::vector<BasePilotPtr> pilots;

	// �`�[���P�̃p�C���b�g�z��
	std::vector<BasePilotPtr> team1Pilots;

	// �`�[��2�̃p�C���b�g�z��
	std::vector<BasePilotPtr> team2Pilots;

	// �`�[��1�̗�
	std::shared_ptr<int> team1Hp = 0;

	// �`�[��2�̗�
	std::shared_ptr<int> team2Hp = 0;

private:

	// �X�^���o�C
	ImagePtr imgStandbay;

	// �S�[
	ImagePtr imgGo;

	// �V�[���؂�ւ����̃t�F�[�h�A�E�g�R���|�[�l���g
	FadeOutPtr fadeOut = nullptr;

	// ���艹��炷���߂̃R���|�[�l���g
	AudioSourcePtr audioSourceSE = nullptr;
};

#endif // !BATTLEMANAGER_H_INCLUDED