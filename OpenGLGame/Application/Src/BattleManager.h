/**
* @file BattleManager.h
*/
#ifndef BATTLEMANAGER_H_INCLUDED
#define BATTLEMANAGER_H_INCLUDED
#include "FGEngine.h"
#include "MsLilst.h"
using namespace FGEngine;
using namespace FGEngine::UI;

class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;

class ControlOwner;
using ControlOwnerPtr = std::shared_ptr<ControlOwner>;

class BattleManager : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	BattleManager() = default;
	virtual ~BattleManager() = default;


	/**
	* �������Ɏ��s
	*/
	virtual void Awake() override;

private:

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

public:

	// �}�b�v�̑傫����
	float mapX;

	// �}�b�v�̑傫���c
	float mapZ;

private:

	// �Q�[�����
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

	float readyTime = 1.5f;

	// �X�^���o�C����
	const float standbayTime = 2;

	// �S�[�^�C��
	const float goTime = 1;

	// �v���C���[
	ControlOwnerPtr playerControl;

	// �G
	ControlOwnerPtr cpuControl;

	// �`�[��1�̗�
	std::shared_ptr<int> teum1Hp = 0;

	// �`�[��2�̗�
	std::shared_ptr<int> teum2Hp = 0;

	// UI
	ImagePtr imgStandbay;
	ImagePtr imgGo;
	ImagePtr imgGoBack;
	ImagePtr imgWin;
	ImagePtr imgLose;
};


#endif // !BATTLEMANAGER_H_INCLUDED
