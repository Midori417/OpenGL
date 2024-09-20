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

private:	// �o�g���Z�b�e�B���O

	/**
	* �o�g���Z�b�e�B���O�Ō��߂��������ƂɃo�g�����[�������߂�
	*/
	void BattleSetting();

	/**
	* �I�u�W�F�N�g�𐶐���ms�ɑΉ������R���|�[�l���g��ǉ�����
	*
	* @param ms �ǉ��������R���|�[�l���g�ɑΉ�����MsList
	*/
	BaseMsPtr CreateMs(MsList ms);

	/**
	* �`�[����ݒ肷��
	*
	* @param control	�ݒ肷��R���g���[��
	* @param id			�`�[��ID
	*/
	void SetTeum(const BasePilotPtr& control, int id);

	/**
	* �o�g���X�^�[�g�ʒu��ݒ肷��
	* 
	* @param pilots	�z�u����p�C���b�g
	* @param id		�`�[��ID
	*/
	void SetBattlePosition(const std::vector<BasePilotPtr>& pilots, int id);

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
	BattleState battleState = BattleState::Battle;

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
	int team1Hp = 0;

	// �`�[��2�̗�
	int team2Hp = 0;

private:

	// �X�^���o�C
	ImagePtr imgStandbay;

	// �S�[
	ImagePtr imgGo;

	// �V�[���؂�ւ����̃t�F�[�h�A�E�g�R���|�[�l���g
	FadeOutPtr fadeOut = nullptr;

	// BGM��炷�R���|�[�l���g
	AudioSourcePtr audioBGM = nullptr;

	// ���艹��炷���߂̃R���|�[�l���g
	AudioSourcePtr audioSE = nullptr;
};

#endif // !BATTLEMANAGER_H_INCLUDED