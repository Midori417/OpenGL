/**
* @file BaseControl.h
*/
#ifndef BASECONTROL_H_INCLUDED
#define BASECONTROL_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

#include "../GameInput.h"

// ��s�錾
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class LookOnCamera;
using LookOnCameraPtr = std::shared_ptr<LookOnCamera>;

/**
* MS�R���g���[���̊��R���|�[�l���g
*/
class BaseControl : public GameEvent
{
protected: // ���̃R���|�[�l���g�p����Ŏ��̉�����

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BaseControl() = default;

public:

	/**
	* �J�n���}
	*/
	void StartOk();

protected:

	/**
	* �R���g���[���̏�����
	*/
	void Initialize();

	/**
	* �J�n����Ă��邩�擾
	*/
	bool IsStart() const;

	/**
	* �^�[�Q�b�g�Ƃ̋������v�Z
	*/
	bool GetDistance() const;

	/**
	* �^�[�Q�b�g�̏�Ԃ��X�V
	*/
	void TargetUpdate();

	/**
	* �@�̂̑�����X�V
	*/
	virtual void GameInputUpdate(){}

protected:

	// �@�̂̑������
	GameInputPtr gameInput = nullptr;

public:

	// ���g�̃J����
	LookOnCameraPtr myCamera = nullptr;

	// ���g�̋@��
	BaseMsPtr myMs = nullptr;

	// ���`�[���̕ʃR���g���[��
	BaseControl* myTeamOtherControl = nullptr;

	// ����`�[���̃R���g���[���z��
	std::vector<BaseControl*> otherTeamControls;

private:

	// ���݂̃^�[�Q�b�g�R���g���[��
	BaseControl* targetControl = nullptr;

	// �J�n������true
	bool isStart = false;
};

#endif // !BASECONTROL_H_INCLUDED
