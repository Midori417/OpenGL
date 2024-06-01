/**
* @file HumanControl.h
*/
#ifndef HYUMANCONTROL_H_INCLUDED
#define HYUMANCONTROL_H_INCLUDED
#include "ControlOwner.h"
using namespace FGEngine::UI;

class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class ImageBlinking;
using ImageBlinkingPtr = std::shared_ptr<ImageBlinking>;
class ImageNum;
using ImageNumPtr = std::shared_ptr<ImageNum>;

/**
* �l�Ԃ�����
*/
class HumanControl : public ControlOwner
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	HumanControl() = default;
	virtual ~HumanControl() = default;


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
	* �Q�[�����͂��X�V
	*/
	virtual void GameInputUpdate() override;

	/**
	* UI�����̍X�V
	*/
	void UIUpdate();

	/**
	* �I������
	*/
	virtual void Finish(VictoryState victoryState) override;

private:

	// ���g�̏��w�i
	ImagePtr imgMyInfoBack;

	// ���g�̋@�̗̂̑�
	ImageNumPtr inMyMsHp;

	// �u�[�X�g�o�[
	ImagePtr imgBoostBar;

	// �u�[�X�g�o�[�̔w�i
	ImagePtr imgBoostBarBack;

	// �u�[�X�g�o�[�̃I�[�o�[�q�[�g
	ImagePtr imgBoostBarOverHeat;

	// �u�[�X�g�o�[�I�[�o�[�q�[�g�[�̓_��
	ImageBlinkingPtr ibBoostBarOverHeat;

	// �o���o�[
	ImagePtr imgBurstBar;

	// �o���o�[�̔w�i
	ImagePtr imgBurstBarBack;

	// ����A�C�R���̔w�i
	std::vector<ImagePtr> imgWeaponBacks;

	// ����̎c�e
	std::vector<ImageNumPtr> inWeaponAmos;

	// ����̎c�e�o�[
	std::vector<ImagePtr> imgWeaponBars;

	// ����̃A�C�R��
	std::vector<ImagePtr> imgWeapnIcons;

	// �^�[�Q�b�g�}�[�N
	ImagePtr imgTargetMark;

	// �^�[�Q�b�g�}�[�N�̃e�N�X�`��
	TexturePtr texTargetMark01;
	TexturePtr texTargetMark02;
	TexturePtr texTargetMark03;

	// �^�[�Q�b�g�̏��
	std::vector<ImagePtr> imgOtherTeumMsInfoBacks;

	// �^�[�Q�b�g�̗̑̓o�[
	std::vector<ImagePtr> imgOtherTeumMsHpBars;

	ImagePtr imgMyTeumOtherMsInfo;
	ImagePtr imgMyTeumOtherMsHpBar;

	// �p�[�g�i�[�@�̗͔̑g�`
	ImagePtr imgPartnerHpBack;

	// �p�[�g�i�[�@�̗̑�
	ImageNumPtr inPartnerMsHp;

	// ����
	ImagePtr imgTimer;

	// �`�[���̗͂̃t���[��
	ImagePtr imgTeamHpFrame;

	// ���`�[���̗̑̓o�[
	ImagePtr imgMyTeamHpBar;

	// ����`�[���̗̑̓o�[
	ImagePtr imgOtherTeamHpBar;

	// ����
	ImagePtr imgWin;

	// �s�k
	ImagePtr imgLose;
};


#endif // !PLAYER_H_INCLUDED
