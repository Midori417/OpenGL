/**
* @file MagunamBullet.h
*/
#ifndef MAGUNAMBULLET_H_INCLUDED
#define MAGUNAMBULLET_H_INCLUDED
#include "FGEngineSub.h"
using namespace FGEngine;

class MagunamBullet :public MonoBehaviour
{
public:

	// === �R���X�g���N�^�E�f�X�g���N�^ === //
	MagunamBullet() = default;
	virtual ~MagunamBullet() = default;

	// === Component��{�C�x���g === //
	virtual void Awake() override;
	virtual void Update() override;
	virtual void OnCollisionEnter(const CollisionPtr collision) override;

	/**
	* �^�[�Q�b�g�̐ݒ�
	* 
	* @param target �^�[�Q�b�g
	*/
	void SetTargetTrs(Transform* target)
	{
		targetTrs = target;
	}

	/**
	* �z�[�~���O�̐ݒ�
	* 
	* @param value true�z�[�~���O����:falase�z�[�~���O�s��
	*/
	void SetHoming(bool value)
	{
		isHoming = value;
	}

	void SetTeum(int value)
	{
		teum = value;
	}

private:

	Transform* targetTrs = nullptr;
	float speed = 70;			// ���x
	float rotationSpeed = 0.05f;// ���񑬓x
	float homingRate = 0.1f;		// �U����
	float destoryTimer = 10;	// ���Ŏ���
	bool isHoming = true;		// �U�����邩
	float atk = 70;				// �U����
	int teum = -1;
};

#endif // !MAGUNAMBULLET_H_INCLUDED
