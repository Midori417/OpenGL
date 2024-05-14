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
class PlayerControl;
using PlayerControlPtr = std::shared_ptr<PlayerControl>;

class CpuControl;
using CpuControlPtr = std::shared_ptr<CpuControl>;

class BattleManager : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	BattleManager() = default;
	virtual ~BattleManager() = default;

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
	};
	GameState state = GameState::GO;

	// �^�C�}�[
	float timer = 0;

	float readyTime = 1.5f;

	// �X�^���o�C����
	const float standbayTime = 2;

	// �S�[�^�C��
	const float goTime = 1;


	// �v���C���[
	PlayerControlPtr playerControl;

	// �G
	CpuControlPtr cpuControl;

	// UI
	ImagePtr imgStandbay;
	ImagePtr imgGo;
	ImagePtr imgGoBack;
};


#endif // !BATTLEMANAGER_H_INCLUDED
