/**
* @file HumanPilot.h
*/
#ifndef HYUMANPILOT_H_INCLUDED
#define HYUMANPILOT_H_INCLUDED
#include "BasePilot.h"
#include "FGEngine/Asset/Texture.h"

class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class ImageBlinking;
using ImageBlinkingPtr = std::shared_ptr<ImageBlinking>;
class ImageNum;
using ImageNumPtr = std::shared_ptr<ImageNum>;

/**
* �l�ԃp�C���b�g
*/
class HumanPilot : public BasePilot
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	HumanPilot() = default;

private:	// �C�x���g

	/**
	* �ŏ��Ɏ��s
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
	* �R���g���[�����X�^�[�g������
	*/
	virtual void ControlStart() override;

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
	TexturePtr texTargetMarkGreen;
	TexturePtr texTargetMarkRed;
	TexturePtr texTargetMarkLock;
	TexturePtr texTargetMarkYellow;

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

#endif // !HYUMANPILOT_H_INCLUDED