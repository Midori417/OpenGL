/**
* @file Player.h
*/
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "ControlOwner.h"
using namespace FGEngine::UI;

class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class LookOnCamera;
using LookOnCameraPtr = std::shared_ptr<LookOnCamera>;
class ImageBlinking;
using ImageBlinkingPtr = std::shared_ptr<ImageBlinking>;
class ImageNum;
using ImageNumPtr = std::shared_ptr<ImageNum>;

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

	/**
	* MS�̍X�V
	*/
	void MsUpdate();

	/**
	* UI�����̍X�V
	*/
	void UIUpdate();

public:
	
	// �J����
	LookOnCameraPtr lookOnCamera;

private:

	ImagePtr imgPlayerInfo;
	ImageNumPtr numPlayerImage;
	ImagePtr imgBoostBar;
	ImagePtr imgBoostBarBack;
	ImagePtr imgBoostBarOverHeat;
	ImageBlinkingPtr ibBoostBarOverHeat;
	ImagePtr imgBurstBar;
	ImagePtr imgBurstBarBack;
	std::vector<ImagePtr> imgWeaponBack;
	ImagePtr imgTargetMark;
	TexturePtr texTargetMark01;
	TexturePtr texTargetMark02;
	TexturePtr texTargetMark03;
	ImagePtr imgTargetInfo;
	ImagePtr imgTargetHPBar;
	ImagePtr imgTimer;
	ImagePtr imgTeumFrame;
	ImagePtr imgTeumHpBar;
	ImagePtr imgTeumEnemyBar;

	// ����
	float distance = 0;
};


#endif // !PLAYER_H_INCLUDED
