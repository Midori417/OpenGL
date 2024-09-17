/**
* @file BasePilot.h
*/
#ifndef BASEPILOT_H_INCLUDED
#define BASEPILOT_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;


// ��s�錾
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class CameraManager;
using CameraManagerPtr = std::shared_ptr<CameraManager>;
enum class VictoryState;
struct GameInput;
using GameInputPtr = std::shared_ptr<GameInput>;

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
	* ���`�[���Ƒ���`�[���̗̑͂�ݒ�
	* 
	* @param myTeamHp		���`�[���̗̑̓|�C���^�[
	* @param otherTeamHp	����`�[���̗̑̓|�C���^�[
	*/
	void SetTeamHP(int* myTeumHp, int* otherTeumHp);

	/**
	* �I��
	*/
	virtual void Finish(VictoryState victoryState){}

	/**
	* �`�[���̗͂𖳌��ɂ���
	*/
	void TeamHPInivinit();

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

	// ���`�[���̕ʃI�[�i
	BasePilot* myTeamOtherOwner = nullptr;

	// ����`�[���̃I�[�i�z��
	std::vector<BasePilot*> otherTeamOwner;

	// �����ʒu�z��
	std::vector<Vector3> responPoss;

protected:

	// �Q�[������
	GameInputPtr gameInput;

	// �R���g���[���̃X�^�[�g�̗L��
	bool isStart = false;

	// ������MS�̎��S�̗L��
	bool isMsDeath = false;

	// ���݂̃^�[�Q�b�g�I�[�i�[
	BasePilot* targetOwner = nullptr;

	// ���͂��X�V���邩
	bool isInputUpdate = true;

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
