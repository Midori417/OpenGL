/**
* @file PlayerManager.h
*/
#ifndef PLAYERMANAGER_H_INCLUDED
#define PLAYERMANAGER_H_INCLUDEED
#include "FGEngineSub.h"
using namespace FGEngine;

// ��s�錾
class BaseMS;
using BaseMSPtr = std::shared_ptr<BaseMS>;
class CameraMove;
using CameraMovePtr = std::shared_ptr<CameraMove>;

/**
* �v���C���[�Ǘ��N���X
*/
class PlayerManager : public MonoBehaviour
{
public:

	// �R���X�g���N�^
	PlayerManager() = default;

	// �f�X�g���N�^
	virtual ~PlayerManager() = default;

	// �����C�x���g
	virtual void Awake() override;

	// �����̎擾
	float GetDistance() const;

private:

	// �C�x���g
	virtual void Start() override;
	virtual void Update() override;

public:

	BaseMSPtr myMs;				// �K���_���R���|�[�l���g
	BaseMSPtr enemyMs;		// �^�[�Q�b�g�R���|�[�l���g
	CameraMovePtr cameraMove;	// �J�����̋����R���|�[�l���g

	// UI
	ImagePtr imgHpBack;			// Hp�̔w�i
	TextPtr txtHp;
	ImagePtr imgBoostbarBack;	// Boostbar�̔w�i
	ImagePtr imgBoostbar;		// boostbar
	ImagePtr imgTargetMark;		// �^�[�Q�b�g�J�[�\��
	ImagePtr imgTargetMsInfo;	// �^�[�Q�b�g���
	ImagePtr imgTargetMSHpBar;
	std::vector<ImagePtr> imgWeaponBacks;		
	std::vector<ImagePtr> imgWeaponIcons;		
	std::vector<TextPtr> txtWeapons;
};

#endif // !PLAYERMANAGER_H_INCLUDED
