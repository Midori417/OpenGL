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
class ControlOwner : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	ControlOwner() = default;
	virtual ~ControlOwner() = default;

	/**
	* �R���g���[�����X�^�[�g������
	*/
	void StartOk();

	/**
	* ���`�[���Ƒ���`�[���̗̑͂�ݒ�
	* 
	* @param myTeumHp		���`�[���̗̑̓|�C���^�[
	* @param otherTeumHp	����`�[���̗̑̓|�C���^�[
	*/
	void SetTeumHP(int* myTeumHp, int* otherTeumHp);

	/**
	* �I��
	*/
	virtual void Finish(VictoryState victoryState){}


protected:

	/**
	* �R���g���[���̏�����
	*/
	void Initialize();

	/**
	* �Q�[�����͂��X�V
	*/
	virtual void GameInputUpdate(){}


	/**
	* ���`�[���̗̑͂��擾
	*/
	int& MyTeumHp() const;

	/**
	* ����`�[���̗̑͂��擾
	*/
	int& OtherTeumHp() const;

	/**
	* �`�[���̗͂����炷
	*/
	void TeumHpSud();

	/**
	* �������擾
	*/
	float GetDistance();

public:

	// �J����
	LookOnCameraPtr myCamera = nullptr;

	// �����̋@��
	BaseMsPtr myMs = nullptr;

	// ���`�[���̕ʃI�[�i
	ControlOwner* myTeumOtherOwner = nullptr;

	// ����`�[���̃I�[�i�z��
	std::vector<ControlOwner*> otherTeumOwner;

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

	// Ms�̑���ł��邩
	bool isMsControl = true;

	// �����^�C�}�[
	float responTimer = 0;

	// ��������܂ł̎���
	float responTime = 3.0f;

private:

	// ���`�[���̗̑�
	int* myTeumHp = 0;

	// ����`�[���̗̑�
	int* otherTeumHp = 0;

};


#endif // !CONTROLOWNER_H_INCLUDED
