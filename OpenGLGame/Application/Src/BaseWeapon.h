/**
* @file BaseWeapon.h
*/
#ifndef BASEWEAPON_H_INCLUDED
#define BASEWEAPON_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

/**
* �����̊��N���X
*/
class BaseWeapon
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	BaseWeapon() = default;
	virtual ~BaseWeapon() = default;

	/**
	* �����̏�����
	*/
	virtual void Initialize(){}

public:

	// �����̖��O
	std::string name = "";
};

/**
* UI�̕\�����镐���̊��N���X
*/
class UIWeapon : public BaseWeapon
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	UIWeapon() = default;
	virtual ~UIWeapon() = default;

public:

	// �c�e�}�b�N�X
	float amoMax = 0;

	// �c�e
	float amo = 0;

	// �����[�h�^�C�}�[
	float reloadTimer = 0;

	// �����[�h�^�C��
	float reloadTime = 0;

	// ����A�C�R��
	TexturePtr iconTexture;
};
/**
* �ˌ�����
*/
class ShotWeapon : public BaseWeapon
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	ShotWeapon() = default;
	virtual ~ShotWeapon() = default;

public:

	/**
	* �e
	*/
	struct Bullet
	{
		// �^����_���[�W
		float damage = 0;

		// �U����
		float homingPower = 0;

		// �^����_�E���l
		float downPower = 0;

		// ���x
		float speed = 0;

		// ���b�V��
		StaticMeshPtr mesh;

		//�V�F�[�_
		ShaderPtr shader;

		// �e�V�F�[�_
		ShaderPtr shadowShader;
	};
	Bullet bullet;
};

/**
* �ˌ�����(UI)
*/
class ShotWeaponUI : public UIWeapon
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	ShotWeaponUI() = default;
	virtual ~ShotWeaponUI() = default;

public:

	ShotWeapon::Bullet bullet;
};
#endif // !BASEWEAPON_H_INCLUDED
