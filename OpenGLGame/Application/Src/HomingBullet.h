/**
* @file HomingBullet.h
*/
#ifndef HOMINGBULLET_H_INCLUDED
#define HOMINGBULLET_H_INCLUDED
#include "BaseBullet.h"

// ��s�錾
class BaseMs;

// �e�̊��N���X
class HomingBullet : public BaseBullet
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	HomingBullet() = default;
	virtual ~HomingBullet() = default;

	/**
	* �^�[�Q�b�g��ݒ�
	*
	* @param targetMs �^�[�Q�b�g�@��
	*/
	void SetTargetMs(BaseMs* targetMs);

private:

	/**
	* �������Ɏ��s
	*/
	virtual void Awake() override;

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update()override;

	// ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
	virtual void OnTriggerEnter(const CollisionPtr other) override;

public:

	// �z�[�~���O��
	float homingSpeed = 0;

	// �z�[�~���O�̗L��
	bool isHoming = true;

private:

	// �^�[�Q�b�gMs
	BaseMs* targetMs = nullptr;

	Vector3 basePos = Vector3::zero;
};

#endif // !HOMINGBULLET_H_INCLUDED