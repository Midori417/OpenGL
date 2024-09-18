/**
* @file BasePilot.h
*/
#ifndef BASEPILOT_H_INCLUDED
#define BASEPILOT_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

// ��s�錾
class BasePilot;
using BasePilotPtr = std::shared_ptr<BasePilot>;
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class CameraManager;
using CameraManagerPtr = std::shared_ptr<CameraManager>;
struct GameInput;
using GameInputPtr = std::shared_ptr<GameInput>;
enum class VictoryState;

/**
* �p�C���b�g�̊��R���|�[�l���g
*/
class BasePilot : public GameEvent
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BasePilot() = default;

private: // �C�x���g

	/**
	* ���ɃN���[������\�肪�Ȃ��̂ŉ��������Ȃ�
	*/
	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

public:

	/**
	* �R���g���[�����X�^�[�g������
	*/
	virtual void ControlStart(){}

	/**
	* �I��
	*/
	virtual void Finish(VictoryState victoryState) {}

public:

	/**
	* ���`�[���Ƒ���`�[���̗̑͂�ݒ�
	* 
	* @param myTeamHp		���`�[���̗̑̓|�C���^�[
	* @param otherTeamHp	����`�[���̗̑̓|�C���^�[
	*/
	void SetTeamHP(int* myTeumHp, int* otherTeumHp);

	/**
	* �p�[�g�i�[�p�C���b�g��ݒ�
	* 
	* @param �ݒ肷��p�[�g�i�[�p�C���b�g
	*/
	void SetPartnerPilot(const BasePilotPtr& pilot);

	/**
	* ����`�[���̃p�C���b�g��ݒ�
	* 
	* @param �ݒ肷�鑊��`�[���̃p�C���b�g
	*/
	void SetOtherTeamPilot(const BasePilotPtr& pilot);

protected:

	/**
	* �R���g���[���̏�����
	*/
	void Initialize();

	/**
	* ���g�̋@�����S���Ƃ��̏���
	*/
	void MyMsDeadUpdate();

	/**
	* �Q�[�����͂��X�V
	*/
	virtual void GameInputUpdate(){}

	/**
	* �^�[�Q�b�g�̏���
	*/
	void TargetUpdate();

	/**
	* ���`�[���̗̑͂��擾
	*/
	int& MyTeamHp() const;

	/**
	* �p�[�g�i�[�p�C���b�g���擾
	*/
	BasePilot* GetPartnerPilot() const;

	/**
	* �p�[�g�i�[�̋@�̂��擾
	*/
	BaseMsPtr GetPartnerMs() const;

	/**
	* ����`�[���̃p�C���b�g���擾
	* 
	* @param index �p�C���b�g�ԍ�
	*/
	BasePilot* GetOtherTeamPilot(size_t index) const;

	/**
	* ����`�[���̋@�̂��擾
	*
	* @param index �p�C���b�g�ԍ�
	*/
	BaseMsPtr GetOtherTeamMs(size_t index) const;

	/**
	* ����`�[���̃p�C���b�g�̐����擾
	*/
	size_t GetOtherTeamPilotSize() const;

	/**
	* �^�[�Q�b�g�p�C���b�g���擾
	*/
	BasePilot* GetTargetPilot() const;

	/**
	* �^�[�Q�b�g�@�̂��擾
	*/
	BaseMsPtr GetTargetMs() const;

	/**
	* ����`�[���̗̑͂��擾
	*/
	int& OtherTeamHp() const;

	/**
	* �`�[���̗͂����炷
	*/
	void TeumHpSud();

	/**
	* �������擾
	*/
	float GetDistance();

	/**
	* �`�[���̗͂��������ǂ���
	*/
	bool GetTeumHPInifinit() const;

public:

	// �J�����Ǘ��}�l�[�W���[
	CameraManagerPtr myCamera = nullptr;

	// �����̋@��
	BaseMsPtr myMs = nullptr;

	// �����ʒu�z��
	std::vector<Vector3> responPoss;

protected:

	// �Q�[������
	GameInputPtr gameInput;

	// �R���g���[���̃X�^�[�g�̗L��
	bool isStart = false;

	// ������MS�̎��S�̗L��
	bool isMsDeath = false;

	// ���͂��X�V���邩
	bool isInputUpdate = true;

private:

	// ���݂̃^�[�Q�b�g�p�C���b�g
	BasePilot* targetPilot = nullptr;

	// �p�[�g�i�[�p�C���b�g
	BasePilot* partnerPilot = nullptr;

	// ����`�[���p�C���b�g�z��
	std::vector<BasePilot*> otherTeamPilots;

private:

	// �����^�C�}�[
	float responTimer = 0;

	// ��������܂ł̎���
	float responTime = 3.0f;

private:

	// ���`�[���̗̑�
	int* myTeamHp = 0;

	// ����`�[���̗̑�
	int* otherTeamHp = 0;

	// true = �`�[���̗́�
	bool isTeamHpInfinit = false;
};

#endif // !BASEPILOT_H_INCLUDED
