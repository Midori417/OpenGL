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

	/**
	* ���X�|�[���ʒu
	*/
	void SetResponPos(const Vector3& pos);
	void SetResponPos(const std::vector<Vector3>& poses);

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

	// �o�g�����
	static BattleInfoPtr battleInfo;

	std::vector<ControlOwnerPtr> controlOwners;

	// �`�[���P�R���g���[���z��
	std::vector<ControlOwnerPtr> teum1ControlOwners;

	// �`�[��2�R���g���[���z��
	std::vector<ControlOwnerPtr> teum2ControlOwners;
	
	// �`�[��1�̗�
	std::shared_ptr<int> teum1Hp = 0;

	// �`�[��2�̗�
	std::shared_ptr<int> teum2Hp = 0;

	// ���A�ʒu
	// �z�� 0=Teum1,1 = Teum2�̏����ʒu
	std::vector<Vector3> responPoses;

	// �o�g���^�C��
	float battleTimer = 0;

	// === UI === //

	// �X�^���o�C
	ImagePtr imgStandbay;

	// �S�[
	ImagePtr imgGo;

	// �S�[�̔w�i
	ImagePtr imgGoBack;

	AudioSourcePtr audioSource;
};


#endif // !BATTLEMANAGER_H_INCLUDED
