/**
* @file ControlOwner.h
*/
#ifndef CONTROLOWNER_H_INCLUDED
#define CONTROLOWNER_H_INCLUDED
#include "FGEngine.h"
#include "MsLilst.h"
using namespace FGEngine;

// ��s�錾
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class LookOnCamera;
using LookOnCameraPtr = std::shared_ptr<LookOnCamera>;
enum class VictoryState;
struct GameInput;
using GameInputPtr = std::shared_ptr<GameInput>;

/**
* ����
*/
class ControlOwner : public GameEvent
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	ControlOwner() = default;
	virtual ~ControlOwner() = default;

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

	virtual ComponentPtr Clone() const override
	{
		return nullptr;

	}

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

	// �J����
	LookOnCameraPtr myCamera = nullptr;

	// �����̋@��
	BaseMsPtr myMs = nullptr;

	// ���`�[���̕ʃI�[�i
	ControlOwner* myTeamOtherOwner = nullptr;

	// ����`�[���̃I�[�i�z��
	std::vector<ControlOwner*> otherTeamOwner;

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
	ControlOwner* targetOwner = nullptr;

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


#endif // !CONTROLOWNER_H_INCLUDED
