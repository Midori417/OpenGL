/**
* @file HomingBullet.h
*/
#ifndef HOMINGBULLET_H_INCLUDED
#define HOMINGBULLET_H_INCLUDED
#include "BaseBullet.h"
#include "FGEngine/Math/Vector3.h"

// ��s�錾
class BaseMs;

/**
* �U���e
*/
class HomingBullet : public BaseBullet
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	HomingBullet() = default;

private: // �C�x���g

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	/**
	* �N���[�����쐬����
	*/
	virtual ComponentPtr Clone() const override;

private:

	/**
	* �z�[�~���O�\���`�F�b�N
	* 
	* @retval true	�z�[�~���O�\
	* @retval flase	�z�[�~���O�s��
	*/
	bool HomingCheck() const;

	/**
	* �z�[�~���O����
	*/
	void Homing() const;

public:

	/**
	* �p�����[�^��ݒ�
	* 
	* @param damage			�^����_���[�W
	* @param speed			�e�̑���
	* @param destroyTime	���ł���܂ł̎���
	* @param homingPower	�U����
	*/
	void SetParamater(float damage, float speed, float destroyTime, float homingPower = 0);

	/**
	* �^�[�Q�b�g�@�̂�ݒ�
	* �ݒ肵�Ȃ��ꍇ�܂�������Ԓe�ɂȂ�
	*/
	void SetTarget(BaseMs* target);

private:

	// �U����
	float homingPower = 0;

	// true�Ȃ�U���e�ɂ���
	bool isHoming = false;

	// �^�[�Q�b�g�̋@��
	BaseMs* target = nullptr;

	// ���ˈʒu
	Vector3 shotPos = Vector3::zero;
};

#endif // !HOMINGBULLET_H_INCLUDED
