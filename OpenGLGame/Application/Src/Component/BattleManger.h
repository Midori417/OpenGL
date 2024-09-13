/**
* @file BattleManager.h
*/
#ifndef BATTLEMANAGER_H_INCLUDED
#define BATTLEMANAGER_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/Math/Vector3.h"
using namespace FGEngine;

// ��s�錾
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class BaseControl;
using BaseControlPtr = std::shared_ptr<BaseControl>;
struct BattleSettingInfo;
using BattleSettingInfoPtr = std::shared_ptr<BattleSettingInfo>;
enum class MsList;

/**
* �o�g���V�[���Ǘ��R���|�[�l���g
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
	* �o�g�����[����ݒ肷��
	*/
	void BattleSetting();

	/**
	* ms�ɑΉ�����R���|�[�l���g��obj�ɒǉ�����
	*
	* @param obj �ǉ�����I�u�W�F�N�g
	* @param ms �ǉ��������R���|�[�l���g�ɑΉ�����MsList
	*/
	BaseMsPtr SetMs(GameObjectPtr& obj, MsList ms);

	/**
	* �`�[����ݒ肷��
	* 
	* @param control	�ݒ肷��R���g���[��
	* @param id			�`�[��ID
	*/
	void SetTeum(const BaseControlPtr& control, int id);

public:

	/**
	* ���X�|�[���ʒu��ݒ�
	* 
	* @param poses �ݒ肵�������X�|�[���ʒu�z��
	*/
	void SetResponPos(const std::vector<Vector3>& poses);

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

	// �o�g������
	float battleTime = 0;

private:

	// �V�[���؂�ւ����̃t�F�[�h�A�E�g�R���|�[�l���g
	FadeOutPtr fadeOut = nullptr;

	// ���艹��炷���߂̃R���|�[�l���g
	AudioSourcePtr audioSource = nullptr;

	// ���A�ʒu
	// �z�� 0=Teum1,1 = Teum2�̏����ʒu
	std::vector<Vector3> responPoses;

private:

	// �o�g���ݒ�V�[���Őݒ肵�����
	BattleSettingInfoPtr battleSettingInfo = nullptr;

	// �`�[��1�̗�
	std::shared_ptr<int> teum1Hp = 0;

	// �`�[��1��̗͖����ɂ��邩
	bool isTeum1HpInfinity = false;

	// �`�[��2�̗�
	std::shared_ptr<int> teum2Hp = 0;

	// �`�[��2��̗͖����ɂ��邩
	bool isTeum2HpInfinity = false;

	// �R���g���[���I�[�i�z��
	std::vector<BaseControlPtr> controls;

	// �`�[���P�R���g���[���z��
	std::vector<BaseControlPtr> teum1Controls;

	// �`�[��2�R���g���[���z��
	std::vector<BaseControlPtr> teum2Controls;

private: // UI

	// �X�^���o�C��\������C���[�W�R���|�[�l���g
	ImagePtr imgStandbay = nullptr;

	// �S�[��\������C���[�W�R���|�[�l���g
	ImagePtr imgGo = nullptr;
};

#endif // !BATTLEMANGER_H_INCLUDED
