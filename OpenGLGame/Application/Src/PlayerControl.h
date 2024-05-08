/**
* @file Player.h
*/
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "ControlOwner.h"
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;

class LookOnCamera;
using LookOnCameraPtr = std::shared_ptr<LookOnCamera>;

/**
* �v���C���[����
*/
class PlayerControl : public ControlOwner
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	PlayerControl() = default;
	virtual ~PlayerControl() = default;

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
	* ���t���[�����s(Update����)
	*/
	virtual void LateUpdate() override;

public:
	
	// �J����
	LookOnCameraPtr lookOnCamera;
};


#endif // !PLAYER_H_INCLUDED
